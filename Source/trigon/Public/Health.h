#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Health.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TRIGON_API UHealth : public UActorComponent
{
	GENERATED_BODY()

public:
	UHealth();

protected:
	virtual void SetupHealthComponent();
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere)
	int Health;

public:
	virtual int GetHealth();
	virtual void TakeDamage(int Damage);
	virtual void Die();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};
