#include "RogueAIController.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"


ARogueAIController::ARogueAIController()
{
}

void ARogueAIController::BeginPlay()
{
	Super::BeginPlay();
	
	RunBehaviorTree(BehaviorTree);
	
	UBlackboardComponent* BB = GetBlackboardComponent();

	AActor* PlayerActor =  UGameplayStatics::GetPlayerPawn(this, 0);
	
	FName PlayerActorKeyName = TEXT("PlayerActor");
	BB->SetValueAsObject(PlayerActorKeyName, PlayerActor);
}

