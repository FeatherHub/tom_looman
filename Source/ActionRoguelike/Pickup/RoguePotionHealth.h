#pragma once

#include "CoreMinimal.h"
#include "RoguePotionBase.h"
#include "RoguePotionHealth.generated.h"


UCLASS()
class ACTIONROGUELIKE_API ARoguePotionHealth : public ARoguePotionBase
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, Category=Potion)
	float HealthIncreaseAmount;

protected:
	virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

public:
	ARoguePotionHealth();
};
