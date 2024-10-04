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
	void SetComponentDefaults(float fireRate, TSubclassOf<AProjectile> bullet);

protected:
	virtual void BeginPlay() override;
	void UpdateClosestEnemy();
	void RotateTowardsClosestEnemy();
	void HandleShoot();
	void Shoot() const;
	bool IsSightToActorObstructed(const AActor* Enemy) const;
	UPROPERTY()
	AActor* OwnerActor;
	AActor* GetClosestActor(TArray<AActor*> Actors) const;
	TArray<AActor*> GetAllSurroundingEnemyActors() const;
	TArray<AActor*> GetAllSurroundingActors() const;
	float GetDistanceToActor(const AActor* Actor) const;
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
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};
