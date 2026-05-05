#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "URogueAction.generated.h"

UCLASS()
class ACTIONROGUELIKE_API URogueAction : public UObject
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditDefaultsOnly, Category="Action")
	FName ActionName = FName(TEXT("PrimaryAttack"));
	
public:
	void StartAction();
	FName GetActionName() const { return ActionName; }
};
