#include "RoguePlayerCharacter.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "ActionSystem/RogueActionSystemComponent.h"
#include "Core/RogueDebug.h"
#include "Core/RogueGameType.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Projectile/RogueProjectileBase.h"

ARoguePlayerCharacter::ARoguePlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	ActionSystemComp = CreateDefaultSubobject<URogueActionSystemComponent>(TEXT("ActionSystemComp"));
	
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	SpringArmComp->SetupAttachment(RootComponent);
	
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->SetupAttachment(SpringArmComp);
	
	JumpMaxCount = 2;
	
	AttackDelay = 0.2f;
}


void ARoguePlayerCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	ActionSystemComp->OnHealthChanged.AddDynamic(this, &ThisClass::OnHealthChanged);
}

void ARoguePlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	EIC->BindAction(IA_Move, ETriggerEvent::Triggered, this, &ThisClass::Move);
	EIC->BindAction(IA_Look, ETriggerEvent::Triggered, this, &ThisClass::Look);
	EIC->BindAction(IA_Jump, ETriggerEvent::Triggered, this, &ThisClass::Jump);
	EIC->BindAction(IA_PrimaryAttack, ETriggerEvent::Triggered, this, &ThisClass::StartSpawn, ProjectileMagicClass);
	EIC->BindAction(IA_BlackholeAttack, ETriggerEvent::Triggered, this, &ThisClass::StartSpawn, ProjectileBlackholeClass);
	EIC->BindAction(IA_Teleport, ETriggerEvent::Triggered, this, &ThisClass::StartSpawn, ProjectileTeleportClass);
}

void ARoguePlayerCharacter::Move(const FInputActionValue& InValue)
{
	FVector2D Value = InValue.Get<FVector2D>();

	FRotator ControlRot = GetControlRotation();
	ControlRot.Pitch = 0.f;
	
	// forward & backward 
	AddMovementInput(ControlRot.Vector(), Value.X);

	// right & left
	FVector RightDirection = ControlRot.RotateVector(FVector::RightVector);
	AddMovementInput(RightDirection, Value.Y);
}

void ARoguePlayerCharacter::Look(const FInputActionInstance& InInstance)
{
	FVector2D Value = InInstance.GetValue().Get<FVector2D>();

	AddControllerYawInput(Value.X);
	AddControllerPitchInput(Value.Y);
}

void ARoguePlayerCharacter::Jump()
{
	Super::Jump();
}

void ARoguePlayerCharacter::StartSpawn(TSubclassOf<ARogueProjectileBase> ProjectileClass)
{
	PlayAnimMontage(AnimMontage_Attack);
	
	FVector SpawnLocation = GetMesh()->GetSocketLocation(MuzzleSocketName);
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, CastingEffect, SpawnLocation, GetControlRotation(), FVector::OneVector, false);
	UGameplayStatics::PlaySound2D(this, CastingSound);
	
	FTimerHandle TimerHandle;
	FTimerDelegate TimerDelegate;
	TimerDelegate.BindUObject(this, &ThisClass::SpawnProjectile, ProjectileClass);
		
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDelegate, AttackDelay, false);
}

void ARoguePlayerCharacter::SpawnProjectile(TSubclassOf<ARogueProjectileBase> ProjectileClass)
{
	FVector SpawnLocation = GetMesh()->GetSocketLocation(MuzzleSocketName);
	
	FVector EyeLocation = CameraComp->GetComponentLocation();
	FVector TraceEnd = EyeLocation + GetControlRotation().Vector() * 5000.f;

	FHitResult Hit;
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);

	FVector AdjustedTargetLocation;
	if (GetWorld()->LineTraceSingleByChannel(Hit, EyeLocation, TraceEnd, RogueCollision::Trace::Projectile, QueryParams))
	{
		AdjustedTargetLocation = Hit.Location; 
	}
	else
	{
		AdjustedTargetLocation = TraceEnd;
	}
	
	FRotator SpawnRotation = (AdjustedTargetLocation - SpawnLocation).Rotation();

	FActorSpawnParameters SpawnParams;
	SpawnParams.Instigator = this;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	AActor* SpawnedProjectile = GetWorld()->SpawnActor<AActor>(ProjectileClass, SpawnLocation, SpawnRotation, SpawnParams);
	MoveIgnoreActorAdd(SpawnedProjectile);
	
#if !UE_BUILD_SHIPPING
	const float DebugDrawTime = CVarProjectileDrawDebug.GetValueOnGameThread();
	if (DebugDrawTime > 0.0f)
	{
		// line trace 
		DrawDebugLine(GetWorld(), EyeLocation, TraceEnd, FColor::Green, false, DebugDrawTime);

		// adjusted projectile path
		DrawDebugLine(GetWorld(), SpawnLocation, AdjustedTargetLocation, FColor::Cyan, false, DebugDrawTime);

		// original projectile path
		DrawDebugLine(GetWorld(), SpawnLocation, SpawnLocation + GetControlRotation().Vector() * 5000.f, FColor::Red, false, DebugDrawTime);

		DrawDebugBox(GetWorld(), TraceEnd, FVector{20.f}, FColor::Green, false, DebugDrawTime);
	}
#endif
}

void ARoguePlayerCharacter::OnHealthChanged(float NewHealth, float OldHealth)
{
	if (NewHealth <= 0.f)
	{
		PlayAnimMontage(AnimMontage_Death);

		DisableInput(nullptr);
		
		GetMovementComponent()->Deactivate();
	}
}

float ARoguePlayerCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	float ActualDamage =  Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	ActionSystemComp->ApplyHealthChange(-ActualDamage);
	
	return ActualDamage;
}
