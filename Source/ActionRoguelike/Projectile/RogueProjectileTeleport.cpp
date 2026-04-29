#include "RogueProjectileTeleport.h"

#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"


ARogueProjectileTeleport::ARogueProjectileTeleport()
{
	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	InFlightNiagaraComp = CreateDefaultSubobject<UNiagaraComponent>(TEXT("InFlightNiagaraComp"));
	MovementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("MovementComp"));
	
	RootComponent = SphereComp;
	InFlightNiagaraComp->SetupAttachment(SphereComp);

	SphereComp->SetCollisionProfileName("Projectile");
	
	InFlightNiagaraComp->bAutoActivate = true;
	
	MovementComp->InitialSpeed = 500.f;
	MovementComp->ProjectileGravityScale = 0.f;
	
	TeleportDelay = 3.f;
}

void ARogueProjectileTeleport::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	
	SphereComp->OnComponentHit.AddDynamic(this, &ThisClass::OnHit);
	SphereComp->IgnoreActorWhenMoving(GetInstigator(), true);
}

void ARogueProjectileTeleport::BeginPlay()
{
	Super::BeginPlay();
	
	GetWorldTimerManager().SetTimer(TeleportTimerHandle, this, &ThisClass::Teleport, TeleportDelay);

	UGameplayStatics::PlaySoundAtLocation(this, SpawnSoundEffect, GetActorLocation(), FRotator::ZeroRotator);
}


void ARogueProjectileTeleport::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	Teleport();
}

void ARogueProjectileTeleport::Teleport()
{
	GetWorldTimerManager().ClearTimer(TeleportTimerHandle);

	APawn* Shooter = GetInstigator();
	if (IsValid(Shooter))
	{
		Shooter->SetActorLocation(GetActorLocation());
	}

	UGameplayStatics::PlaySoundAtLocation(this, TeleportSoundEffect, GetActorLocation(), FRotator::ZeroRotator);
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, TeleportNiagaraEffect, GetActorLocation());
	
	Destroy();
}
