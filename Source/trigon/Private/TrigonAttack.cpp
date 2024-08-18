#include "TrigonAttack.h"
#include "PlayerHealth.h"

UTrigonAttack::UTrigonAttack()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTrigonAttack::BeginPlay()
{
	Super::BeginPlay();
	InitializeComponent();
}

void UTrigonAttack::InitializeComponent()
{
	Super::InitializeComponent();
	Owner = GetOwner();
	if (!Owner)
	{
		return;
	}

	CapsuleComponent = Owner->FindComponentByClass<UCapsuleComponent>();
	if (CapsuleComponent)
	{
		CapsuleComponent->OnComponentBeginOverlap.AddDynamic(this, &UTrigonAttack::OnOverlapBegin);
	}
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
	UHealth* PlayerHealth = OtherActor->FindComponentByClass<UHealth>();
	if (PlayerHealth)
	{
		PlayerHealth->TakeDamage(AttackDamage);
		Owner->Destroy();
	}
}

void UTrigonAttack::TickComponent(const float DeltaTime, const ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}
