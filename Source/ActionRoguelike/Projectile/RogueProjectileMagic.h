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
	TObjectPtr<USphereComponent> SphereComp;
	
	UPROPERTY(VisibleAnywhere, Category=Component)
	TObjectPtr<UProjectileMovementComponent> ProjectileMovementComp;
	
	UPROPERTY(VisibleAnywhere, Category=Component)
	TObjectPtr<UNiagaraComponent> NiagaraComp;

	UPROPERTY(VisibleAnywhere, Category=Component)
	TObjectPtr<UAudioComponent> AudioComp;
	
	UPROPERTY(EditDefaultsOnly, Category=Effect)
	TObjectPtr<UNiagaraSystem> ExplosionNiagaraEffect;

	UPROPERTY(EditDefaultsOnly, Category=Effect)
	TObjectPtr<USoundBase> ExplosionSoundEffect;

	UPROPERTY(EditDefaultsOnly, Category=Damage)
	TSubclassOf<UDamageType> DamageTypeClass;
	
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	
public:
	ARogueProjectileMagic();

	virtual void PostInitializeComponents() override;
};
