#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RogueProjectileBase.generated.h"

class USphereComponent;
class UProjectileMovementComponent;
class UNiagaraSystem;
class UNiagaraComponent;

UCLASS(Abstract)
class ACTIONROGUELIKE_API ARogueProjectileBase : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, Category=Component)
	TObjectPtr<UProjectileMovementComponent> MovementComp;

	UPROPERTY(VisibleAnywhere, Category=Component)
	TObjectPtr<USphereComponent> SphereComp;
	
	UPROPERTY(EditDefaultsOnly, Category=Effect)
	TObjectPtr<UNiagaraSystem> SpawnNiagaraEffect;

	UPROPERTY(EditDefaultsOnly, Category=Effect)
	TObjectPtr<USoundBase> SpawnSoundEffect;
	
	UPROPERTY(VisibleAnywhere, Category=Component)
	TObjectPtr<UNiagaraComponent> InFlightNiagaraComp;

	UPROPERTY(VisibleAnywhere, Category=Component)
	TObjectPtr<UAudioComponent> InFlightAudioComp;
	
	UPROPERTY(EditDefaultsOnly, Category=Effect)
	TObjectPtr<UNiagaraSystem> ExplosionNiagaraEffect;

	UPROPERTY(EditDefaultsOnly, Category=Effect)
	TObjectPtr<USoundBase> ExplosionSoundEffect;

protected:
	UFUNCTION()
	virtual void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	
	UFUNCTION()
	virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult ) {};
	
	virtual void Explode();
	
public:
	ARogueProjectileBase();
	virtual void PostInitializeComponents() override;

protected:
	virtual void BeginPlay() override;
};
