#include "Health.h"

UHealth::UHealth()
{
	PrimaryComponentTick.bCanEverTick = true;
	Health = 100;
}

void UHealth::BeginPlay()
{
	Super::BeginPlay();
	SetupHealthComponent();
}

void UHealth::SetupHealthComponent()
{
	Health = 100;
}

void UHealth::TickComponent(const float DeltaTime, const ELevelTick TickType,
                            FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

int UHealth::GetHealth()
{
	return Health;
}

void UHealth::TakeDamage(const int Damage)
{
	Health -= Damage;
	if (Health <= 0)
	{
		Die();
	}
}

void UHealth::Die()
{
}
