#include "TrigonMovement.h"

#include "AIController.h"
#include "NavigationSystem.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

UTrigonMovement::UTrigonMovement()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTrigonMovement::BeginPlay()
{
	Super::BeginPlay();
}

void UTrigonMovement::TickComponent(const float DeltaTime, const ELevelTick TickType,
                                    FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	UpdatePlayerPosition();
	MoveTowardsPlayer();
}

void UTrigonMovement::UpdatePlayerPosition()
{
	const ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if (!PlayerCharacter)
	{
		return;
	}

	PlayerPosition = PlayerCharacter->GetActorLocation();
}

void UTrigonMovement::MoveTowardsPlayer() const
{
	const APawn* Owner = Cast<APawn>(GetOwner());
	if (!Owner)
	{
		return;
	}

	// Had to add "AIModule", "NavigationSystem" into trigon.build.cs for any of this to not throw errors in build
	AAIController* AIController = Cast<AAIController>(Owner->GetController());
	if (!AIController)
	{
		return;
	}

	const UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetCurrent(GetWorld());
	if (!NavSystem)
	{
		return;
	}

	AIController->MoveToLocation(PlayerPosition);
}
