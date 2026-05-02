#include "RogueActionSystemComponent.h"


bool URogueActionSystemComponent::ApplyHealthChange(float InHealthDelta)
{
	float OldHealth = AttributeSet.Health; 
	float NewHealth = FMath::Clamp(AttributeSet.Health + InHealthDelta, 0.f, AttributeSet.MaxHealth);
	
	if (!FMath::IsNearlyEqual(OldHealth, NewHealth))
	{
		AttributeSet.Health = NewHealth;
		OnHealthChanged.Broadcast(NewHealth, OldHealth);
		return true;
	}
	
	UE_LOG(LogTemp, Log, TEXT("[HEALTH] Max: %-6.1f, New: %-6.1f, Delta: %-6.1f"), AttributeSet.MaxHealth, NewHealth, InHealthDelta);
	return false;
}
