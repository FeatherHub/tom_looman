#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RogueProjectileTeleport.generated.h"

class UProjectileMovementComponent;
class USphereComponent;
class UNiagaraSystem;
class UNiagaraComponent;
class UAudioComponent;
class USoundBase;

UCLASS()
class ACTIONROGUELIKE_API ARogueProjectileTeleport : public AActor
{
	GENERATED_BODY()
protected:
	UPROPERTY(VisibleAnywhere, Category = "Component")
	TObjectPtr<USphereComponent> SphereComp;
	
	UPROPERTY(VisibleAnywhere, Category = "Component")
	TObjectPtr<UProjectileMovementComponent> MovementComp;
	
	UPROPERTY(VisibleAnywhere, Category = "Component|Effect")
	TObjectPtr<UNiagaraComponent> InFlightNiagaraComp;
	
	UPROPERTY(EditDefaultsOnly, Category = Effect)
	TObjectPtr<USoundBase> SpawnSoundEffect;

	UPROPERTY(EditDefaultsOnly, Category = "Effect|Teleport")
	TObjectPtr<UNiagaraSystem> TeleportNiagaraEffect;
	
	UPROPERTY(EditDefaultsOnly, Category = "Effect|Teleport")
	TObjectPtr<USoundBase> TeleportSoundEffect;

	UPROPERTY(EditDefaultsOnly, Category = Teleport)
	float TeleportDelay;
	
	FTimerHandle TeleportTimerHandle;
	
protected:
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	void Teleport();
	
public:
	ARogueProjectileTeleport();
	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;
};
