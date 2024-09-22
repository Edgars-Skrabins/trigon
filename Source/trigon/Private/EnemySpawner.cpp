#include "EnemySpawner.h"

AEnemySpawner::AEnemySpawner(): CanSpawnEnemy(true)
{
	PrimaryActorTick.bCanEverTick = true;
}

void AEnemySpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	HandleSpawnEnemy();
}

void AEnemySpawner::HandleSpawnEnemy()
{
	if (CanSpawnEnemy)
	{
		CanSpawnEnemy = false;
		SpawnEnemy();
		GetWorld()->GetTimerManager().SetTimer(SpawnRateTimer, this, &AEnemySpawner::ResetSpawnRateTimer, SpawnRate, false);
	}
}

void AEnemySpawner::SpawnEnemy()
{
	FVector SpawnLocation = GetActorLocation();
	FRotator SpawnRotation = GetActorRotation();
	GetWorld()->SpawnActor<AActor>(Enemy, SpawnLocation, SpawnRotation);
}

void AEnemySpawner::ResetSpawnRateTimer()
{
	CanSpawnEnemy = true;
}
