#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "RoguePlayerCharacter.generated.h"

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
	
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
