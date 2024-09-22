#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemySpawner.generated.h"

UCLASS()
class TRIGON_API AEnemySpawner : public AActor
{
	GENERATED_BODY()

public:
	AEnemySpawner();

protected:
	UPROPERTY(BlueprintReadWrite)
	float SpawnRate;
	UPROPERTY(BlueprintReadWrite)
	TSubclassOf<AActor> Enemy;
	bool CanSpawnEnemy;
	FTimerHandle SpawnRateTimer;
	void HandleSpawnEnemy();
	void SpawnEnemy();
	void ResetSpawnRateTimer();

public:
	virtual void Tick(float DeltaTime) override;
};
