#include "Projectile.h"

#include "Health.h"
#include "Components/SphereComponent.h"

AProjectile::AProjectile()
{
	PrimaryActorTick.bCanEverTick = true;
	Damage = 100;
}

void AProjectile::BeginPlay()
{
	Super::BeginPlay();
}

void AProjectile::InitializeComponent()
{
	SphereComponent = FindComponentByClass<USphereComponent>();
	if (SphereComponent)
	{
		SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &AProjectile::OnOverlapBegin);
	}
}

void AProjectile::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                                 int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor->ActorHasTag("Enemy"))
	{
		HandleEnemyCollision(OtherActor);
	}
}

void AProjectile::HandleEnemyCollision(const AActor* OtherActor)
{
	UHealth* EnemyHealth = OtherActor->FindComponentByClass<UHealth>();
	if (EnemyHealth)
	{
		EnemyHealth->TakeDamage(Damage);
		Destroy();
	}
}

void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
