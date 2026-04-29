// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RogueProjectileBlackhole.generated.h"

class URadialForceComponent;
class UNiagaraSystem;
class UNiagaraComponent;
class UProjectileMovementComponent;
class USphereComponent;
class USoundBase;
class UAudioComponent;

UCLASS()
class ACTIONROGUELIKE_API ARogueProjectileBlackhole : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, Category=Component)
	TObjectPtr<USphereComponent> SphereComp;
	
	UPROPERTY(VisibleAnywhere, Category=Component)
	TObjectPtr<UProjectileMovementComponent> ProjectileMovementComp;
	
	UPROPERTY(VisibleAnywhere, Category="Component|Effect")
	TObjectPtr<UNiagaraComponent> InFlightNiagaraComp;

	UPROPERTY(VisibleAnywhere, Category="Component|Effect")
	TObjectPtr<UAudioComponent> InFlightAudioComp;
	
	UPROPERTY(EditDefaultsOnly, Category=Effect)
	TObjectPtr<UNiagaraSystem> ExplosionNiagaraEffect;

	UPROPERTY(EditDefaultsOnly, Category=Effect)
	TObjectPtr<USoundBase> ExplosionSoundEffect;

	UPROPERTY(EditDefaultsOnly, Category="Effect|Attack")
	TObjectPtr<URadialForceComponent> BlackholeRadialForceComp;
	
protected:
	void OnExplode();
	
public:
	ARogueProjectileBlackhole();
	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;
	
	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult );
};
