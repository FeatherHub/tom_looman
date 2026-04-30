#include "RoguePlayerCharacter.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Projectile/RogueProjectileBase.h"

ARoguePlayerCharacter::ARoguePlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	SpringArmComponent->SetupAttachment(RootComponent);
	
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComponent->SetupAttachment(SpringArmComponent);
	
	JumpMaxCount = 2;
}

void ARoguePlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	EIC->BindAction(IA_Move, ETriggerEvent::Triggered, this, &ThisClass::Move);
	EIC->BindAction(IA_Look, ETriggerEvent::Triggered, this, &ThisClass::Look);
	EIC->BindAction(IA_Jump, ETriggerEvent::Triggered, this, &ThisClass::Jump);
	EIC->BindAction(IA_PrimaryAttack, ETriggerEvent::Triggered, this, &ThisClass::PrimaryAttack);
	EIC->BindAction(IA_BlackholeAttack, ETriggerEvent::Triggered, this, &ThisClass::BlackholeAttack);
	EIC->BindAction(IA_Teleport, ETriggerEvent::Triggered, this, &ThisClass::Teleport);
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

void ARoguePlayerCharacter::PrimaryAttack()
{
	PlayAnimMontage(AnimMontage_Attack);
	
	FVector SpawnLocation = GetMesh()->GetSocketLocation(MuzzleSocketName);
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, CastingEffect, SpawnLocation, GetControlRotation(), FVector::OneVector, false);
	UGameplayStatics::PlaySound2D(this, CastingSound);
	
	const float Delay = 0.3f;
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ThisClass::PrimaryAttackTimeElapsed, Delay);
}

void ARoguePlayerCharacter::PrimaryAttackTimeElapsed()
{
	FVector SpawnLocation = GetMesh()->GetSocketLocation(MuzzleSocketName);
	FRotator SpawnRotator = GetControlRotation();
	FActorSpawnParameters SpawnParams;
	SpawnParams.Instigator = this;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	AActor* SpawnedProjectile = GetWorld()->SpawnActor<AActor>(ProjectileMagicClass, SpawnLocation, SpawnRotator, SpawnParams);
	MoveIgnoreActorAdd(SpawnedProjectile);

	UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, FireEffect, SpawnLocation);
	UGameplayStatics::PlaySound2D(this, FireSound);
}

void ARoguePlayerCharacter::BlackholeAttack()
{
	FVector SpawnLocation = GetMesh()->GetSocketLocation(MuzzleSocketName);
	FRotator SpawnRotator = GetControlRotation();
	FActorSpawnParameters SpawnParams;
	SpawnParams.Instigator = this;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	AActor* SpawnedProjectile = GetWorld()->SpawnActor<AActor>(ProjectileBlackholeClass, SpawnLocation, SpawnRotator, SpawnParams);
	MoveIgnoreActorAdd(SpawnedProjectile);
}

void ARoguePlayerCharacter::Teleport()
{
	FVector SpawnLocation = GetMesh()->GetSocketLocation(MuzzleSocketName);
	FRotator SpawnRotator = GetControlRotation();
	FActorSpawnParameters SpawnParams;
	SpawnParams.Instigator = this;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	AActor* SpawnedProjectile = GetWorld()->SpawnActor<AActor>(ProjectileTeleportClass, SpawnLocation, SpawnRotator, SpawnParams);
	MoveIgnoreActorAdd(SpawnedProjectile);
}
