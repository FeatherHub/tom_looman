#include "RogueProjectileMagic.h"

#include "Components/SphereComponent.h"
#include "NiagaraComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

ARogueProjectileMagic::ARogueProjectileMagic()
{
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	SphereComponent->SetCollisionProfileName("Projectile");
	RootComponent = SphereComponent;

	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("MovementComp"));
	MovementComponent->InitialSpeed = 1000.f;

	NiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraComp"));
	NiagaraComponent->SetupAttachment(SphereComponent);
}
