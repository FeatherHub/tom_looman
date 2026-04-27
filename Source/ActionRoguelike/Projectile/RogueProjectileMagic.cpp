#include "RogueProjectileMagic.h"

#include "Components/SphereComponent.h"
#include "NiagaraComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraFunctionLibrary.h"
#include "Components/AudioComponent.h"

ARogueProjectileMagic::ARogueProjectileMagic()
{
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	SphereComponent->SetCollisionProfileName("Projectile");
	RootComponent = SphereComponent;

	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("MovementComp"));
	MovementComponent->InitialSpeed = 1000.f;
	MovementComponent->ProjectileGravityScale = 0.f;
	
	NiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraComp"));
	NiagaraComponent->SetupAttachment(SphereComponent);

	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComp"));
	AudioComponent->SetupAttachment(SphereComponent);
}

void ARogueProjectileMagic::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	SphereComponent->OnComponentHit.AddDynamic(this, &ThisClass::OnHit);
	
	SphereComponent->IgnoreActorWhenMoving(GetInstigator(), true);
}

void ARogueProjectileMagic::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	FVector HitFromDirection = GetActorRotation().Vector();
	UGameplayStatics::ApplyPointDamage(OtherActor, 10.f, HitFromDirection, Hit, GetInstigatorController(), this, DamageTypeClass);
	
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, ExplodeNiagaraEffect, GetActorLocation());
	UGameplayStatics::PlaySound2D(this, ExplodeSoundEffect);
	
	Destroy();
}
