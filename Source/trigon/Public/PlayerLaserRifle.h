#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "PlayerLaserRifle.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TRIGON_API UPlayerLaserRifle : public USceneComponent
{
	GENERATED_BODY()

public:
	UPlayerLaserRifle();

protected:
	virtual void BeginPlay() override;
	void UpdateClosestEnemy();
	AActor* GetClosestActor(TArray<AActor*> Actors);
	TArray<AActor*> GetAllSurroundingEnemyActors();
	TArray<AActor*> GetAllSurroundingActors();
	float GetDistanceToActor(AActor* Actor);
	UPROPERTY()
	AActor* ClosestEnemy;
	UPROPERTY()
	int EnemyCheckRadius;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
