#pragma once

#include "CoreMinimal.h"
#include "Runtime/AIModule/Classes/AIController.h"
#include "RogueAIController.generated.h"

UCLASS()
class ACTIONROGUELIKE_API ARogueAIController : public AAIController
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, Category=AI)
	TObjectPtr<UBehaviorTree> BehaviorTree;
	
public:
	ARogueAIController();

	virtual void BeginPlay() override;
};
