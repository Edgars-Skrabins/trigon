#pragma once

#include "CoreMinimal.h"
#include "PlayerMovement.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

UCLASS()
class TRIGON_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void SetupInputComponent() override;
	virtual void BeginPlay() override;
	void InitializeComponent();
	UPROPERTY()
	UPlayerMovement* PlayerMovement;

private:
	void MoveVertical(float MoveStrength);
	void MoveHorizontal(float MoveStrength);
};
