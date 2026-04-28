// Fill out your copyright notice in the Description page of Project Settings.


#include "RoguePlayerController.h"

#include "EnhancedInputComponent.h"
#include "RogueInteractionComponent.h"


ARoguePlayerController::ARoguePlayerController()
{
	InteractionComp = CreateDefaultSubobject<URogueInteractionComponent>(TEXT("InteractionComp"));
}

void ARoguePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(InputComponent);

	EIC->BindAction(IA_Interact, ETriggerEvent::Triggered, this, &ThisClass::Interact);
}

void ARoguePlayerController::Interact()
{
	InteractionComp->Interact();
}
