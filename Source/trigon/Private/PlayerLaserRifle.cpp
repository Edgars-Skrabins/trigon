#include "PlayerLaserRifle.h"
#include "Kismet/KismetSystemLibrary.h"

UPlayerLaserRifle::UPlayerLaserRifle(): CanShoot(true)
{
	PrimaryComponentTick.bCanEverTick = true;
	EnemyCheckRadius = 1000.0f;
}

void UPlayerLaserRifle::SetComponentDefaults(const float fireRate, const TSubclassOf<AProjectile> bullet)
{
	FireRate = fireRate;
	Projectile = bullet;
}

void UPlayerLaserRifle::BeginPlay()
{
	Super::BeginPlay();
	OwnerActor = GetOwner();
}

void UPlayerLaserRifle::TickComponent(const float DeltaTime, const ELevelTick TickType,
                                      FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	UpdateClosestEnemy();
	RotateTowardsClosestEnemy();
	HandleShoot();
}

void UPlayerLaserRifle::UpdateClosestEnemy()
{
	const TArray<AActor*> SurroundingEnemyActors = GetAllSurroundingEnemyActors();
	if (SurroundingEnemyActors.Num() <= 0)
	{
		ClosestEnemy = nullptr;
		return;
	}
	ClosestEnemy = GetClosestActor(GetAllSurroundingEnemyActors());
}

void UPlayerLaserRifle::RotateTowardsClosestEnemy()
{
	if (!ClosestEnemy || IsSightToActorObstructed(ClosestEnemy))
	{
		return;
	}

	const FVector PlayerLaserRifleLocation = GetComponentLocation();
	FVector EnemyLocation = ClosestEnemy->GetActorLocation();
	EnemyLocation.Z = PlayerLaserRifleLocation.Z;
	const FVector DirectionToEnemy = (EnemyLocation - PlayerLaserRifleLocation).GetSafeNormal();
	const FRotator RotationToEnemy = DirectionToEnemy.Rotation();

	SetWorldRotation(RotationToEnemy);
}

void UPlayerLaserRifle::HandleShoot()
{
	if (CanShoot && ClosestEnemy)
	{
		if (IsSightToActorObstructed(ClosestEnemy))
		{
			return;
		}

		CanShoot = false;
		Shoot();
		GetWorld()->GetTimerManager().SetTimer(FireRateTimer, this, &UPlayerLaserRifle::ResetFireTimer, FireRate,
		                                       false);
	}
}

void UPlayerLaserRifle::Shoot() const
{
	UWorld* World = GetWorld();
	if (!Projectile || !World)
	{
		return;
	}

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	const FVector SpawnLocation = GetComponentLocation();
	const FRotator SpawnRotation = GetComponentRotation();

	AProjectile* SpawnedProjectile = World->SpawnActor<AProjectile>(Projectile, SpawnLocation, SpawnRotation,
	                                                                SpawnParams);
	// SpawnedProjectile->SetInstigator(OwnerActor);
}

bool UPlayerLaserRifle::IsSightToActorObstructed(const AActor* actor) const
{
	FHitResult OutHit;
	const bool isSightObstructed = UKismetSystemLibrary::LineTraceSingle(
		GetWorld(),
		GetComponentLocation(),
		actor->GetActorLocation(),
		TraceTypeQuery1,
		false,
		{},
		EDrawDebugTrace::None,
		OutHit,
		true
	);

	if (OutHit.GetActor() == actor)
	{
		return false;
	}


	return isSightObstructed;
}

void UPlayerLaserRifle::ResetFireTimer()
{
	CanShoot = true;
}

AActor* UPlayerLaserRifle::GetClosestActor(TArray<AActor*> Actors) const
{
	AActor* ClosestActor = Actors[0];
	float CurrentClosestActorDistance = GetDistanceToActor(ClosestActor);

	for (AActor* Actor : Actors)
	{
		const float DistanceToActor = GetDistanceToActor(Actor);
		if (DistanceToActor < CurrentClosestActorDistance)
		{
			CurrentClosestActorDistance = DistanceToActor;
			ClosestActor = Actor;
		}
	}
	return ClosestActor;
}

TArray<AActor*> UPlayerLaserRifle::GetAllSurroundingEnemyActors() const
{
	TArray<AActor*> EnemyArray;
	TArray<AActor*> Actors = GetAllSurroundingActors();

	for (AActor* Actor : Actors)
	{
		if (Actor && Actor->ActorHasTag("Enemy"))
		{
			EnemyArray.Add(Actor);
		}
	}

	return EnemyArray;
}

TArray<AActor*> UPlayerLaserRifle::GetAllSurroundingActors() const
{
	const FVector CheckCenterLocation = GetComponentLocation();
	TArray<AActor*> Actors;

	UKismetSystemLibrary::SphereOverlapActors(
		GetWorld(),
		CheckCenterLocation,
		EnemyCheckRadius,
		{},
		AActor::StaticClass(),
		{},
		Actors
	);

	return Actors;
}

float UPlayerLaserRifle::GetDistanceToActor(const AActor* Actor) const
{
	const FVector ActorLocation = Actor->GetActorLocation();
	const float DistanceToActor = (ActorLocation - GetComponentLocation()).Size();
	return DistanceToActor;
}
