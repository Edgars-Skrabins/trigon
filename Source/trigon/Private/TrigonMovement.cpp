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
		UE_LOG(LogTemp, Warning, TEXT("Havent found player"));
		return;
	}

	PlayerPosition = PlayerCharacter->GetActorLocation();
}

void UTrigonMovement::MoveTowardsPlayer() const
{
	const APawn* Owner = Cast<APawn>(GetOwner());
	if (!Owner)
	{
		UE_LOG(LogTemp, Warning, TEXT("Havent found owner"));
		return;
	}

	// Had to add "AIModule", "NavigationSystem" into trigon.build.cs for any of this to not throw errors in build
	AAIController* AIController = Cast<AAIController>(Owner->GetController());
	if (!AIController)
	{
		UE_LOG(LogTemp, Warning, TEXT("No AI controller"));
		return;
	}

	const UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetCurrent(GetWorld());
	if (!NavSystem)
	{
		UE_LOG(LogTemp, Warning, TEXT("No Navmesh"));
		return;
	}

	AIController->MoveToLocation(PlayerPosition);
}
