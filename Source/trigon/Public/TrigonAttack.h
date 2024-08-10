#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TrigonAttack.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TRIGON_API UTrigonAttack : public UActorComponent
{
	GENERATED_BODY()

public:
	UTrigonAttack();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnOverlapBegin(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);

	UPROPERTY()
	UStaticMeshComponent* StaticMeshComponent;

	void HandlePlayerCollision(const AActor* OtherActor);

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
