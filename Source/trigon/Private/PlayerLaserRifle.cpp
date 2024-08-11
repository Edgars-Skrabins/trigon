#include "PlayerLaserRifle.h"
#include "Kismet/KismetSystemLibrary.h"

UPlayerLaserRifle::UPlayerLaserRifle()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UPlayerLaserRifle::BeginPlay()
{
	Super::BeginPlay();
}

void UPlayerLaserRifle::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	UpdateClosestEnemy();
}

void UPlayerLaserRifle::UpdateClosestEnemy()
{
	ClosestEnemy = GetClosestActor(GetAllSurroundingEnemyActors());
}

AActor* UPlayerLaserRifle::GetClosestActor(TArray<AActor*> Actors)
{
	AActor* ClosestActor = Actors[0];
	float CurrentClosestActorDistance = GetDistanceToActor(ClosestActor);

	for (AActor* Actor : Actors)
	{
		const float DistanceToActor = GetDistanceToActor(Actor);
		if (DistanceToActor < CurrentClosestActorDistance)
		{
			CurrentClosestActorDistance = DistanceToActor;
			ClosestActor = Actor;
		}
	}
	return ClosestActor;
}

TArray<AActor*> UPlayerLaserRifle::GetAllSurroundingEnemyActors()
{
	TArray<AActor*> EnemyArray;
	TArray<AActor*> Actors = GetAllSurroundingActors();

	for (AActor* Actor : Actors)
	{
		if (Actor && Actor->ActorHasTag("Enemy"))
		{
			EnemyArray.Add(Actor);
		}
	}

	return EnemyArray;
}

TArray<AActor*> UPlayerLaserRifle::GetAllSurroundingActors()
{
	const FVector CheckCenterLocation = GetComponentLocation();
	TArray<AActor*> Actors;

	UKismetSystemLibrary::SphereOverlapActors(
		GetWorld(),
		CheckCenterLocation,
		EnemyCheckRadius,
		{},
		AActor::StaticClass(),
		{},
		Actors
	);

	return Actors;
}

float UPlayerLaserRifle::GetDistanceToActor(AActor* Actor)
{
	const FVector ActorLocation = Actor->GetActorLocation();
	const float DistanceToActor = (ActorLocation - GetComponentLocation()).Size();
	return DistanceToActor;
}
