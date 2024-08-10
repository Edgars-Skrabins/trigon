#include "MyPlayerController.h"
#include "PlayerMovement.h"

void AMyPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindAxis("MoveVertical", this, &AMyPlayerController::MoveVertical);
	InputComponent->BindAxis("MoveHorizontal", this, &AMyPlayerController::MoveHorizontal);
}

void AMyPlayerController::BeginPlay()
{
	Super::BeginPlay();
	InitializeComponent();
}

void AMyPlayerController::InitializeComponent()
{
	PlayerMovement = GetPawn()->FindComponentByClass<UPlayerMovement>();
}

void AMyPlayerController::MoveVertical(float MoveStrength)
{
	if (!PlayerMovement)
	{
		return;
	}
	PlayerMovement->MoveVertical(MoveStrength);
}

void AMyPlayerController::MoveHorizontal(float MoveStrength)
{
	if (!PlayerMovement)
	{
		return;
	}

	PlayerMovement->MoveHorizontal(MoveStrength);
}
