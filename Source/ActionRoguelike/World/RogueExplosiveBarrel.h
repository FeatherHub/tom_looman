#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RogueExplosiveBarrel.generated.h"


class URadialForceComponent;
class UNiagaraSystem;
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
	
	UPROPERTY(VisibleAnywhere, Category=Component)
	TObjectPtr<URadialForceComponent> ExplodeRadialForceComp;
	
	UPROPERTY(EditDefaultsOnly, Category=Effect)
	TObjectPtr<UNiagaraSystem> BurnNiagaraEffect;
	
	UPROPERTY(EditDefaultsOnly, Category=Effect)
	TObjectPtr<UNiagaraSystem> ExplodeNiagaraEffect;

	UPROPERTY(EditDefaultsOnly, Category=Effect)
	TObjectPtr<USoundBase> BurnSoundEffect;

	UPROPERTY(EditDefaultsOnly, Category=Effect)
	TObjectPtr<USoundBase> ExplodeSoundEffect;

	UPROPERTY(EditDefaultsOnly, Category=Damage)
	TSubclassOf<UDamageType> DmgTypeClass;

	UPROPERTY(EditDefaultsOnly, Category=Damage)
	float ExplodeDelay;
	
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	
	
	void Explode();
	
public:
	ARogueExplosiveBarrel();
	virtual void PostInitializeComponents() override;
};
