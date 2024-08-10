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
	const AActor* Owner = GetOwner();
	if (!Owner)
	{
		return;
	}

	CapsuleComponent = Owner->FindComponentByClass<UCapsuleComponent>();
	if (CapsuleComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("Initialize Capsule collision"));
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
