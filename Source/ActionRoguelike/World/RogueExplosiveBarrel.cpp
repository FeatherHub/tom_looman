#include "RogueExplosiveBarrel.h"

#include "Components/BoxComponent.h"

ARogueExplosiveBarrel::ARogueExplosiveBarrel()
{
	SMComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComp"));
	BoxShapeComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxShapeComp"));

	RootComponent = BoxShapeComp; 
	SMComp->SetupAttachment(BoxShapeComp);

	BoxShapeComp->SetSimulatePhysics(true);
	BoxShapeComp->SetEnableGravity(true);
}
