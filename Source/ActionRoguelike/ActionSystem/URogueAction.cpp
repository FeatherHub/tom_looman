#include "URogueAction.h"

void URogueAction::StartAction()
{
	float GameTime = GetWorld()->TimeSeconds;
	UE_LOGFMT(LogTemp, Log, "Start Action '{ActionName}' at {GameTime}", ActionName, GameTime);
}
