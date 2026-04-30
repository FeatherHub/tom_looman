#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RogueActionSystemComponent.generated.h"


USTRUCT(Blueprintable)
struct FAttributeSet
{
	GENERATED_BODY()
	
	FAttributeSet(): Health(100.f) {}
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float Health;
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ACTIONROGUELIKE_API URogueActionSystemComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Attribute)
	FAttributeSet AttributeSet;
	
public:
	void ApplyHealthChange(float InHealthDelta);	
};
