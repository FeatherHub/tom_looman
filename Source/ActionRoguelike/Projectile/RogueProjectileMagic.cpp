#include "RogueProjectileMagic.h"

#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"

void ARogueProjectileMagic::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	SphereComp->OnComponentHit.AddDynamic(this, &ThisClass::OnHit);
	
	DamageAmount = 10.f;
}

void ARogueProjectileMagic::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	Super::OnHit(HitComponent, OtherActor, OtherComp, NormalImpulse, Hit);
	
	Explode();
	
	FVector HitFromDirection = GetActorRotation().Vector();
	UGameplayStatics::ApplyPointDamage(OtherActor, DamageAmount, HitFromDirection, Hit, GetInstigatorController(), this, DamageTypeClass);
	
	Destroy();
}
