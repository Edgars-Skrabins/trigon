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
	void RotateTowardsClosestEnemy();
	void HandleShoot();
	void Shoot();
	AActor* GetClosestActor(TArray<AActor*> Actors);
	TArray<AActor*> GetAllSurroundingEnemyActors();
	TArray<AActor*> GetAllSurroundingActors();
	float GetDistanceToActor(AActor* Actor);
	void ResetFireTimer();
	UPROPERTY()
	AActor* ClosestEnemy;
	UPROPERTY()
	int EnemyCheckRadius;
	UPROPERTY()
	bool CanShoot;
	UPROPERTY(EditAnywhere)
	int FireRate;
	UPROPERTY()
	FTimerHandle FireRateTimer;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AActor> Projectile;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
