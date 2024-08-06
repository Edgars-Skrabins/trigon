#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TrigonMovement.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TRIGON_API UTrigonMovement : public UActorComponent
{
	GENERATED_BODY()

public:
	UTrigonMovement();

protected:
	virtual void BeginPlay() override;
	void UpdatePlayerPosition();
	void MoveTowardsPlayer() const;

	FVector PlayerPosition;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};
