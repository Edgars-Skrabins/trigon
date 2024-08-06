#include "PlayerMovement.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

UPlayerMovement::UPlayerMovement()
{
	MoveSpeed = 5;
	PrimaryComponentTick.bCanEverTick = true;
}

void UPlayerMovement::BeginPlay()
{
	Super::BeginPlay();
}

void UPlayerMovement::MoveVertical(const float Value) const
{
	const float Velocity = Value * MoveSpeed;

	if (const ACharacter* Character = Cast<ACharacter>(GetOwner()))
	{
		Character->GetCharacterMovement()->MoveSmooth(Character->GetActorForwardVector(), Velocity);
	}
}

void UPlayerMovement::MoveHorizontal(const float Value) const
{
	const float Velocity = Value * MoveSpeed;

	if (const ACharacter* Character = Cast<ACharacter>(GetOwner()))
	{
		Character->GetCharacterMovement()->MoveSmooth(Character->GetActorRightVector(), Velocity);
	}
}

void UPlayerMovement::TickComponent(const float DeltaTime, const ELevelTick TickType,
                                    FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}
