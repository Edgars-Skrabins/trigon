#pragma once

#include "CoreMinimal.h"
#include "MySceneComponent.h"
#include "Projectile.h"
#include "PlayerLaserRifle.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TRIGON_API UPlayerLaserRifle : public UMySceneComponent
{
	GENERATED_BODY()

public:
	UPlayerLaserRifle();
	UFUNCTION(BlueprintCallable)
	void SetComponentDefaults(int fireRate, TSubclassOf<AProjectile> bullet);

protected:
	virtual void BeginPlay() override;
	void UpdateClosestEnemy();
	void RotateTowardsClosestEnemy();
	void HandleShoot();
	void Shoot();
	bool CanSeeEnemy(AActor* Enemy);
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
	UPROPERTY()
	float FireRate;
	UPROPERTY()
	FTimerHandle FireRateTimer;
	UPROPERTY()
	TSubclassOf<AProjectile> Projectile;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
