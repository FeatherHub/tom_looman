#include "RogueActionSystemComponent.h"


void URogueActionSystemComponent::ApplyHealthChange(float InHealthDelta)
{
	float OldHealth = AttributeSet.Health; 
	
	AttributeSet.Health += InHealthDelta;

	OnHealthChanged.Broadcast(AttributeSet.Health, OldHealth);
	
	UE_LOG(LogTemp, Log, TEXT("[HEALTH] New: %-6.1f, Old: %-6.1f, Delta: %-6.1f"), AttributeSet.Health, OldHealth, InHealthDelta);
}
