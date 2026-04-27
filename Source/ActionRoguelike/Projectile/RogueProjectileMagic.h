#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RogueProjectileMagic.generated.h"

class UNiagaraSystem;
class UProjectileMovementComponent;
class USphereComponent;
class UNiagaraComponent;

UCLASS(Abstract)
class ACTIONROGUELIKE_API ARogueProjectileMagic : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, Category=Component)
	TObjectPtr<USphereComponent> SphereComponent;
	
	UPROPERTY(VisibleAnywhere, Category=Component)
	TObjectPtr<UProjectileMovementComponent> MovementComponent;
	
	UPROPERTY(VisibleAnywhere, Category=Component)
	TObjectPtr<UNiagaraComponent> NiagaraComponent;

	UPROPERTY(VisibleAnywhere, Category=Component)
	TObjectPtr<UAudioComponent> AudioComponent;
	
	UPROPERTY(EditDefaultsOnly, Category=Effect)
	TObjectPtr<UNiagaraSystem> ExplodeNiagaraEffect;

	UPROPERTY(EditDefaultsOnly, Category=Effect)
	TObjectPtr<USoundBase> ExplodeSoundEffect;

	UPROPERTY(EditDefaultsOnly, Category=Damage)
	TSubclassOf<UDamageType> DamageTypeClass;
	
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	
public:
	ARogueProjectileMagic();

	virtual void PostInitializeComponents() override;
};
