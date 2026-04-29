#include "RogueProjectileBlackhole.h"

#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Components/AudioComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "PhysicsEngine/RadialForceComponent.h"


ARogueProjectileBlackhole::ARogueProjectileBlackhole()
{
	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	ProjectileMovementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComp"));
	InFlightNiagaraComp = CreateDefaultSubobject<UNiagaraComponent>(TEXT("InFlightNiagaraComp"));
	InFlightAudioComp = CreateDefaultSubobject<UAudioComponent>(TEXT("InFlightAudioComp"));
	BlackholeRadialForceComp = CreateDefaultSubobject<URadialForceComponent>(TEXT("BlackholdRadialForceComp"));
	
	RootComponent = SphereComp;
	InFlightAudioComp->SetupAttachment(SphereComp);
	InFlightNiagaraComp->SetupAttachment(SphereComp);
	BlackholeRadialForceComp->SetupAttachment(SphereComp);
	
	ProjectileMovementComp->ProjectileGravityScale = 0.f;
	ProjectileMovementComp->InitialSpeed = 300.f;
	
	BlackholeRadialForceComp->bAutoActivate = true;
	BlackholeRadialForceComp->ForceStrength = -10000000;
}

void ARogueProjectileBlackhole::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnBeginOverlap);
	SphereComp->IgnoreActorWhenMoving(GetInstigator(), true);
}

void ARogueProjectileBlackhole::BeginPlay()
{
	Super::BeginPlay();
	
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ThisClass::OnExplode, 5.f);
}

void ARogueProjectileBlackhole::OnExplode()
{
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, ExplosionNiagaraEffect, GetActorLocation());
	UGameplayStatics::PlaySoundAtLocation(this, ExplosionSoundEffect, GetActorLocation(), FRotator::ZeroRotator);
	
	Destroy();
}

void ARogueProjectileBlackhole::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult )
{
	Other->Destroy();
}