#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "RoguePlayerCharacter.generated.h"

class UNiagaraSystem;
class ARogueProjectileMagic;
struct FInputActionInstance;
struct FInputActionValue;
class UInputAction;
class USpringArmComponent;
class UCameraComponent;

UCLASS()
class ACTIONROGUELIKE_API ARoguePlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ARoguePlayerCharacter();

protected:
	UPROPERTY(VisibleAnywhere, Category=Component)
	TObjectPtr<UCameraComponent> CameraComponent;

	UPROPERTY(VisibleAnywhere, Category=Component)
	TObjectPtr<USpringArmComponent> SpringArmComponent;
	
	UPROPERTY(EditDefaultsOnly, Category=Input)
	TObjectPtr<UInputAction> IA_Move;
	
	UPROPERTY(EditDefaultsOnly, Category=Input)
	TObjectPtr<UInputAction> IA_Look;

	UPROPERTY(EditDefaultsOnly, Category=Input)
	TObjectPtr<UInputAction> IA_Jump;
	
	UPROPERTY(EditDefaultsOnly, Category=Input)
	TObjectPtr<UInputAction> IA_PrimaryAttack;
	
	UPROPERTY(EditDefaultsOnly, Category=Input)
	TObjectPtr<UInputAction> IA_BlackholeAttack;
	
	UPROPERTY(EditDefaultsOnly, Category=Input)
	TObjectPtr<UInputAction> IA_Teleport;
	
	UPROPERTY(EditDefaultsOnly, Category=Attack)
	TSubclassOf<AActor> ProjectileMagicClass;

	UPROPERTY(EditDefaultsOnly, Category=Attack)
	TSubclassOf<AActor> ProjectileBlackholeClass;
	
	UPROPERTY(EditDefaultsOnly, Category=Attack)
	TSubclassOf<AActor> ProjectileTeleportClass;
	
	UPROPERTY(EditDefaultsOnly, Category=Attack)
	FName MuzzleSocketName;
	
	UPROPERTY(EditDefaultsOnly, Category=Attack)
	TObjectPtr<UAnimMontage> AnimMontage_Attack;
	
	UPROPERTY(EditDefaultsOnly, Category=Attack)
	TObjectPtr<UNiagaraSystem> CastingEffect;
	
	UPROPERTY(EditDefaultsOnly, Category=Attack)
	TObjectPtr<USoundBase> CastingSound;	
	
	UPROPERTY(EditDefaultsOnly, Category=Attack)
	TObjectPtr<UNiagaraSystem> FireEffect;
	
	UPROPERTY(EditDefaultsOnly, Category=Attack)
	TObjectPtr<USoundBase> FireSound;	
	
	void Move(const FInputActionValue& InValue);
	void Look(const FInputActionInstance& InInstance);
	virtual void Jump() override;
	void PrimaryAttack();
	void PrimaryAttackTimeElapsed();
	void BlackholeAttack();
	void Teleport();
	
public:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
