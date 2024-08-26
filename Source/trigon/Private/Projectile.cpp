#include "Projectile.h"

#include "Health.h"

AProjectile::AProjectile()
{
	PrimaryActorTick.bCanEverTick = true;
	Damage = 100;
}

void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	InitializeComponent();
}

void AProjectile::InitializeComponent()
{
	MeshComponent = FindComponentByClass<UStaticMeshComponent>();
	if (MeshComponent)
	{
		MeshComponent->OnComponentBeginOverlap.AddDynamic(this, &AProjectile::OnOverlapBegin);
	}
}

void AProjectile::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                                 int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor->ActorHasTag("Player"))
	{
		return;
	}

	if (OtherActor && OtherActor->ActorHasTag("Enemy"))
	{
		HandleEnemyCollision(OtherActor);
		return;
	}

	HandleGeneralCollision(OtherActor);
}

void AProjectile::HandleEnemyCollision(const AActor* OtherActor)
{
	UHealth* EnemyHealth = OtherActor->FindComponentByClass<UHealth>();
	if (EnemyHealth)
	{
		EnemyHealth->TakeDamage(Damage);
	}

	Destroy();
}

void AProjectile::HandleGeneralCollision(const AActor* OtherActor)
{
	Destroy();
}

void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
