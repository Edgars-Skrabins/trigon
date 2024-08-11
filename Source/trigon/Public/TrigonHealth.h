#pragma once

#include "CoreMinimal.h"
#include "Health.h"
#include "TrigonHealth.generated.h"

UCLASS()
class TRIGON_API UTrigonHealth : public UHealth
{
	GENERATED_BODY()

protected:
	virtual void Die() override;
};
