#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RogueActionSystemComponent.generated.h"


struct FAttributeSet
{
	FAttributeSet(): Health(100.f) {}
	
	float Health;
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ACTIONROGUELIKE_API URogueActionSystemComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	FAttributeSet AttributeSet;
	
public:
	void ApplyHealthChange(float InHealthDelta);	
};
