#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class TRIGON_API AProjectile : public AActor
{
	GENERATED_BODY()

public:
	AProjectile();

protected:
	virtual void BeginPlay() override;

	virtual void InitializeComponent();

	UPROPERTY()
	int Damage;

	UFUNCTION()
	void OnOverlapBegin(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);

	UPROPERTY()
	USphereComponent* SphereComponent;
	void HandleEnemyCollision(const AActor* OtherActor);

public:
	virtual void Tick(float DeltaTime) override;
};
