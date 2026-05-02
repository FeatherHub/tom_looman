#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RoguePotionBase.generated.h"


class USphereComponent;

UCLASS(Abstract)
class ACTIONROGUELIKE_API ARoguePotionBase : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, Category=Component)
	TObjectPtr<UStaticMeshComponent> MeshComp;

	UPROPERTY(VisibleAnywhere, Category=Component)
	TObjectPtr<USphereComponent> SphereComp;
	
	UPROPERTY(EditDefaultsOnly, Category=Effect)
	TObjectPtr<USoundBase> PickupSoundEffect;
	
protected:
	UFUNCTION()
	virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {}

	virtual void PlayPickupEffect();
	
public:
	ARoguePotionBase();
	virtual void PostInitializeComponents() override;
};
