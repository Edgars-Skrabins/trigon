#include "TrigonAttack.h"
#include "PlayerHealth.h"

UTrigonAttack::UTrigonAttack()
{
	PrimaryComponentTick.bCanEverTick = true;
	const AActor* Owner = GetOwner();
	if (Owner)
	{
		StaticMeshComponent = Owner->FindComponentByClass<UStaticMeshComponent>();

		StaticMeshComponent->OnComponentBeginOverlap.AddDynamic(this, &UTrigonAttack::OnOverlapBegin);
	}
}

void UTrigonAttack::BeginPlay()
{
	Super::BeginPlay();
}

void UTrigonAttack::OnOverlapBegin(UPrimitiveComponent* OverlappedComp,
                                   AActor* OtherActor,
                                   UPrimitiveComponent* OtherComp,
                                   int32 OtherBodyIndex,
                                   bool bFromSweep,
                                   const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor->ActorHasTag("Player"))
	{
		HandlePlayerCollision(OtherActor);
	}
}
    
void UTrigonAttack::HandlePlayerCollision(const AActor* OtherActor)
{
	UPlayerHealth* PlayerHealth = OtherActor->FindComponentByClass<UPlayerHealth>();
	if (PlayerHealth)
	{
		PlayerHealth->TakeDamage(100);
	}
}

void UTrigonAttack::TickComponent(const float DeltaTime, const ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}
