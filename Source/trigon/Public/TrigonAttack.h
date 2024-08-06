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
	static void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, const AActor* OtherActor, UPrimitiveComponent* OtherComp,
	                           int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY()
	UStaticMeshComponent* StaticMeshComponent;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};
