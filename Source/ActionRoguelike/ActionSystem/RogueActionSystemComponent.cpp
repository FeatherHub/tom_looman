#include "RogueActionSystemComponent.h"


bool URogueActionSystemComponent::ApplyHealthChange(float InHealthDelta)
{
	float OldHealth = AttributeSet.Health; 
	float NewHealth = FMath::Clamp(AttributeSet.Health + InHealthDelta, 0.f, AttributeSet.MaxHealth);
	
	bool bHasChanged = false;
	if (!FMath::IsNearlyEqual(OldHealth, NewHealth))
	{
		AttributeSet.Health = NewHealth;
		bHasChanged = true;
		OnHealthChanged.Broadcast(NewHealth, OldHealth);
	}
	
	UE_LOG(LogTemp, Log, TEXT("[HEALTH] Max: %-6.1f, New: %-6.1f, Delta: %-6.1f"), AttributeSet.MaxHealth, NewHealth, InHealthDelta);
	
	return bHasChanged;
}
