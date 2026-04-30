#include "RogueProjectileTeleport.h"

#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"


ARogueProjectileTeleport::ARogueProjectileTeleport()
{
	MovementComp->InitialSpeed = 500.f;
	
	TeleportDelay = 3.f;
}

void ARogueProjectileTeleport::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	
	SphereComp->OnComponentHit.AddDynamic(this, &ThisClass::OnHit);
}

void ARogueProjectileTeleport::BeginPlay()
{
	Super::BeginPlay();
	
	GetWorldTimerManager().SetTimer(TeleportTimerHandle, this, &ThisClass::Explode, TeleportDelay);
}


void ARogueProjectileTeleport::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	Explode();
}

void ARogueProjectileTeleport::Explode()
{
	Super::Explode();

	GetWorldTimerManager().ClearTimer(TeleportTimerHandle);

	APawn* Shooter = GetInstigator();
	if (IsValid(Shooter))
	{
		Shooter->SetActorLocation(GetActorLocation());
	}
	
	Destroy();
}
