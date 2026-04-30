#include "RogueActionSystemComponent.h"


void URogueActionSystemComponent::ApplyHealthChange(float InHealthDelta)
{
	AttributeSet.Health += InHealthDelta;
	
	UE_LOG(LogTemp, Log, TEXT("New Health: %f, Delta: %f"), AttributeSet.Health, InHealthDelta);
}
