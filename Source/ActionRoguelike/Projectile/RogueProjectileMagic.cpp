#include "RogueProjectileMagic.h"

#include "Components/SphereComponent.h"
#include "NiagaraComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraFunctionLibrary.h"

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
}

void ARogueProjectileMagic::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	SphereComponent->OnComponentHit.AddDynamic(this, &ThisClass::OnHit);
	
	SphereComponent->IgnoreActorWhenMoving(GetInstigator(), true);
}

void ARogueProjectileMagic::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	TSubclassOf<UDamageType> DamageType = UDamageType::StaticClass();

	UGameplayStatics::ApplyDamage(OtherActor, 10.f, GetInstigatorController(), this, DamageType);
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, NiagaraSystem, GetActorLocation());
	
	Destroy();
}
