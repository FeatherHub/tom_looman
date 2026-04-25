#include "RoguePlayerCharacter.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"


ARoguePlayerCharacter::ARoguePlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	SpringArmComponent->SetupAttachment(RootComponent);
	
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComponent->SetupAttachment(SpringArmComponent);
}

void ARoguePlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ARoguePlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ARoguePlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

