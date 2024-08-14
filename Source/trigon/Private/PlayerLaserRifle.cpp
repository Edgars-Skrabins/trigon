#include "PlayerLaserRifle.h"
#include "Kismet/KismetSystemLibrary.h"

UPlayerLaserRifle::UPlayerLaserRifle()
{
	PrimaryComponentTick.bCanEverTick = true;
	EnemyCheckRadius = 1000.0f;
}

void UPlayerLaserRifle::BeginPlay()
{
	Super::BeginPlay();
}

void UPlayerLaserRifle::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	UpdateClosestEnemy();
	RotateTowardsClosestEnemy();
	HandleShoot();
}

void UPlayerLaserRifle::UpdateClosestEnemy()
{
	const TArray<AActor*> SurroundingEnemyActors = GetAllSurroundingEnemyActors();
	if (SurroundingEnemyActors.Num() <= 0)
	{
		ClosestEnemy = nullptr;
		return;
	}
	ClosestEnemy = GetClosestActor(GetAllSurroundingEnemyActors());
}

void UPlayerLaserRifle::RotateTowardsClosestEnemy()
{
	if (!ClosestEnemy)
	{
		return;
	}

	const FVector PlayerLaserRifleLocation = GetComponentLocation();
	const FVector EnemyLocation = ClosestEnemy->GetActorLocation();
	const FVector DirectionToEnemy = (EnemyLocation - PlayerLaserRifleLocation).GetSafeNormal();
	const FRotator RotationToEnemy = DirectionToEnemy.Rotation();

	SetWorldRotation(RotationToEnemy);
}

void UPlayerLaserRifle::HandleShoot()
{
	if (CanShoot)
	{
		CanShoot = false;
		Shoot();
		GetWorld()->GetTimerManager().SetTimer(FireRateTimer, this, &UPlayerLaserRifle::ResetFireTimer, FireRate, false);
	}
}

void UPlayerLaserRifle::Shoot()
{
	UWorld* World = GetWorld();
	if (!Projectile || !World)
	{
		return;
	}

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	const FVector SpawnLocation = GetComponentLocation();
	const FRotator SpawnRotation = GetComponentRotation();

	// Spawn the projectile
	AActor* SpawnedProjectile = World->SpawnActor<AActor>(Projectile, SpawnLocation, SpawnRotation, SpawnParams);
}

void UPlayerLaserRifle::ResetFireTimer()
{
	CanShoot = false;
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
