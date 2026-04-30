#include "RogueActionSystemComponent.h"


void URogueActionSystemComponent::ApplyHealthChange(float InHealthDelta)
{
	float OldHealth = AttributeSet.Health; 
	float MaxHealth = GetDefault<URogueActionSystemComponent>()->AttributeSet.Health;
	float NewHealth = FMath::Clamp(AttributeSet.Health + InHealthDelta, 0.f, MaxHealth);
	
	if (!FMath::IsNearlyEqual(OldHealth, NewHealth))
	{
		AttributeSet.Health = NewHealth;
		OnHealthChanged.Broadcast(NewHealth, OldHealth);
	}
	
	UE_LOG(LogTemp, Log, TEXT("[HEALTH] Max: %-6.1f, New: %-6.1f, Delta: %-6.1f"), MaxHealth, NewHealth, InHealthDelta);
}
