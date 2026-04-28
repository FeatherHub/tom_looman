#pragma once

#include "CoreMinimal.h"
#include "Core/RogueInteractionInterface.h"
#include "GameFramework/Actor.h"
#include "RogueItemChest.generated.h"

UCLASS()
class ACTIONROGUELIKE_API ARogueItemChest : public AActor, public IRogueInteractionInterface
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, Category=Component)
	TObjectPtr<UStaticMeshComponent> LidMeshComp;
	
	UPROPERTY(VisibleAnywhere, Category=Component)
	TObjectPtr<UStaticMeshComponent> BaseMeshComp;

	UPROPERTY(EditDefaultsOnly, Category=Animation)
	float AnimationPitchMax = 120.f;

	UPROPERTY(EditDefaultsOnly, Category=Animation)
	float AnimationPitchSpeed = 20.f;
	
	float AnimationPitchCurrent = 0.f;
	
protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent)
	void OnItemChestOpenAnimationComplete();
public:
	ARogueItemChest();
	virtual void Tick(float DeltaTime) override;
	
	virtual void Interact_Implementation() override;
};
