#include "RogueProjectileBlackhole.h"

#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"


ARogueProjectileBlackhole::ARogueProjectileBlackhole()
{
	BlackholeRadialForceComp = CreateDefaultSubobject<URadialForceComponent>(TEXT("BlackholdRadialForceComp"));
	BlackholeRadialForceComp->SetupAttachment(SphereComp);
	BlackholeRadialForceComp->bAutoActivate = true;
	BlackholeRadialForceComp->ForceStrength = -10000000;
	
	BlackholeLifeTime = 1.f;
	MovementComp->InitialSpeed = 600.f;
}

void ARogueProjectileBlackhole::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnBeginOverlap);
}

void ARogueProjectileBlackhole::BeginPlay()
{
	Super::BeginPlay();
	
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ThisClass::Explode, BlackholeLifeTime);
}

void ARogueProjectileBlackhole::Explode()
{
	Super::Explode();
	
	Destroy();
}

void ARogueProjectileBlackhole::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult )
{
	Other->Destroy();
}