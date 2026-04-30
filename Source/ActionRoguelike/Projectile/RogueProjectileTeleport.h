#pragma once

#include "CoreMinimal.h"
#include "RogueProjectileBase.h"
#include "GameFramework/Actor.h"
#include "RogueProjectileTeleport.generated.h"

UCLASS()
class ACTIONROGUELIKE_API ARogueProjectileTeleport : public ARogueProjectileBase
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditDefaultsOnly, Category = Teleport)
	float TeleportDelay;
	
	FTimerHandle TeleportTimerHandle;
	
protected:
	virtual void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) override;

	virtual void Explode() override;
	
protected:
	virtual void BeginPlay() override;

public:
	ARogueProjectileTeleport();
	virtual void PostInitializeComponents() override;
};
