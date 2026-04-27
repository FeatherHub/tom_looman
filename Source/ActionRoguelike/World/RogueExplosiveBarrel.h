#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RogueExplosiveBarrel.generated.h"


class UBoxComponent;
class UStaticMeshComponent;

UCLASS()
class ACTIONROGUELIKE_API ARogueExplosiveBarrel : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, Category=Component)
	TObjectPtr<UStaticMeshComponent> SMComp;
	
	UPROPERTY(VisibleAnywhere, Category=Component)
	TObjectPtr<UBoxComponent> BoxShapeComp;
	
public:
	ARogueExplosiveBarrel();
};
