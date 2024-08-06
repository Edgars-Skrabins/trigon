#include "MyPlayerController.h"
#include "PlayerMovement.h"

void AMyPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAxis("MoveVertical", this, &AMyPlayerController::MoveVertical);
	InputComponent->BindAxis("MoveHorizontal", this, &AMyPlayerController::MoveHorizontal);
}

void AMyPlayerController::MoveVertical(float MoveStrength)
{
	if (const UPlayerMovement* PlayerMovement = GetPawn()->FindComponentByClass<UPlayerMovement>())
	{
		PlayerMovement->MoveVertical(MoveStrength);
	}
}

void AMyPlayerController::MoveHorizontal(float MoveStrength)
{
	if (const UPlayerMovement* PlayerMovement = GetPawn()->FindComponentByClass<UPlayerMovement>())
	{
		PlayerMovement->MoveHorizontal(MoveStrength);
	}
}
