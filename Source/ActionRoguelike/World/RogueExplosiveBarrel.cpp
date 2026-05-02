#include "RogueExplosiveBarrel.h"

#include "NiagaraFunctionLibrary.h"
#include "ActionRoguelike/Projectile/RogueProjectileMagic.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "PhysicsEngine/RadialForceComponent.h"


ARogueExplosiveBarrel::ARogueExplosiveBarrel()
{
	SMComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComp"));
	BoxShapeComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxShapeComp"));
	RootComponent = BoxShapeComp;
	SMComp->SetupAttachment(BoxShapeComp);

	BoxShapeComp->SetSimulatePhysics(true);
	BoxShapeComp->SetEnableGravity(true);

	ExplodeRadialForceComp = CreateDefaultSubobject<URadialForceComponent>(TEXT("RadialForceComp"));
	ExplodeRadialForceComp->SetupAttachment(RootComponent);
	
	ExplodeDelay = 2.f;

	SMComp->SetCanEverAffectNavigation(false);
}

void ARogueExplosiveBarrel::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	
	BoxShapeComp->OnComponentHit.AddDynamic(this, &ThisClass::OnHit);
}

void ARogueExplosiveBarrel::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (!OtherActor->IsA<ARogueProjectileMagic>())
	{		
		return;
	}	
	
	// @Todo: remove effects
	UGameplayStatics::SpawnSoundAttached(BurnSoundEffect, RootComponent);
	UNiagaraFunctionLibrary::SpawnSystemAttached(BurnNiagaraEffect, RootComponent, NAME_None, FVector::ZeroVector, FRotator::ZeroRotator, EAttachLocation::Type::SnapToTarget, true);
	
	FTimerHandle DelayTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(DelayTimerHandle, this, &ThisClass::Explode, ExplodeDelay);
}

void ARogueExplosiveBarrel::Explode()
{
	UGameplayStatics::PlaySound2D(this, ExplodeSoundEffect);
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, ExplodeNiagaraEffect, GetActorLocation());

	UGameplayStatics::ApplyRadialDamage(this, 10.f, GetActorLocation(), ExplodeRadialForceComp->Radius, DmgTypeClass, {this});
	
	ExplodeRadialForceComp->FireImpulse();
	
	BoxShapeComp->AddImpulse(FVector::UpVector * 1000.f, NAME_None, true);
	BoxShapeComp->AddAngularImpulseInDegrees(FVector::RightVector * 100.f, NAME_None, true);
}
