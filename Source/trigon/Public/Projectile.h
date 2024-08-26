#pragma once

#include "CoreMinimal.h"
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
	UStaticMeshComponent* MeshComponent;
	void HandleEnemyCollision(const AActor* OtherActor);

	void HandleGeneralCollision(const AActor* OtherActor);

public:
	virtual void Tick(float DeltaTime) override;
};
