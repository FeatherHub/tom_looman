#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RogueActionSystemComponent.generated.h"


USTRUCT(Blueprintable)
struct FAttributeSet
{
	GENERATED_BODY()
	
	FAttributeSet()
	{
		MaxHealth = 100.f;
		Health = MaxHealth;
	}
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float Health;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float MaxHealth;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHealthChanged, float, NewHealth, float, OldHealth);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ACTIONROGUELIKE_API URogueActionSystemComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable, Category=Attribute)
	FOnHealthChanged OnHealthChanged;
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Attribute)
	FAttributeSet AttributeSet;
	
public:
	bool ApplyHealthChange(float InHealthDelta);	
};
