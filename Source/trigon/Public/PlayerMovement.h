#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PlayerMovement.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TRIGON_API UPlayerMovement : public UActorComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Movement settings")
	float MoveSpeed;

protected:
	virtual void BeginPlay() override;
	virtual void InitializeComponent() override;

	UPROPERTY()
	ACharacter* Character;
	UPROPERTY()
	UCharacterMovementComponent* CharacterMovementComponent;

public:
	UPlayerMovement();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	void MoveVertical(float Value) const;
	void MoveHorizontal(float Value) const;
};
