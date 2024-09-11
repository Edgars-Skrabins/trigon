#pragma once

#include "CoreMinimal.h"
#include "MySceneComponent.h"
#include "Projectile.h"
#include "Components/SceneComponent.h"
#include "PlayerLaserRifle.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TRIGON_API UPlayerLaserRifle : public UMySceneComponent
{
	GENERATED_BODY()

public:
	UPlayerLaserRifle();
	UFUNCTION(BlueprintCallable)
	void SetComponentDefaults(int fireRate);

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
	UPROPERTY(BlueprintReadWrite)
	float FireRate;
	UPROPERTY(EditDefaultsOnly)
	FTimerHandle FireRateTimer;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AProjectile> Projectile;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
