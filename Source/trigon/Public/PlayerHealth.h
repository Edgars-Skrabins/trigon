#pragma once

#include "CoreMinimal.h"
#include "Health.h"
#include "PlayerHealth.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))

class TRIGON_API UPlayerHealth : public UHealth
{
	GENERATED_BODY()

public:
	UPlayerHealth();
};
