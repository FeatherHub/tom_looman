#include "RoguePotionHealth.h"

#include "ActionSystem/RogueActionSystemComponent.h"


ARoguePotionHealth::ARoguePotionHealth()
{
	HealthIncreaseAmount = 20.f;
}

void ARoguePotionHealth::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnBeginOverlap(OverlappedComp, Other, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	URogueActionSystemComponent* ASC = Other->GetComponentByClass<URogueActionSystemComponent>();
	if (!ASC)
	{
		return;
	}


	
	if (ASC->ApplyHealthChange(HealthIncreaseAmount))
	{
		PlayPickupEffect();
		Destroy();		
	}
}
