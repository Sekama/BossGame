// Richard Hill


#include "Sunbeam.h"

#include "Components/CapsuleComponent.h"
#include "GP4/CustomComponents/Health/HealthComponent.h"
#include "GP4/Player/PlayerCharacter.h"

ASunbeam::ASunbeam()
{
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Collision Capsule"));
	CapsuleComponent->SetCollisionProfileName("NoCollision");
	RootComponent = CapsuleComponent;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Sunbeam Mesh"));
	Mesh->SetupAttachment(CapsuleComponent);
	Mesh->SetCollisionProfileName("NoCollision");
}

void ASunbeam::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASunbeam::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CheckDetonationTime(DeltaTime);
}

void ASunbeam::CheckDetonationTime(float DeltaTime)
{
	if (DetonationTimer < DetonationTime)
	{
		DetonationTimer += DeltaTime;
	}
	else if (!bHasDetonated)
	{
		Detonate();
		bHasDetonated = true;
	}
}

void ASunbeam::Detonate()
{
	UE_LOG(LogTemp,Warning,TEXT("Detonate"));
	
	// Collision Sweep
	FHitResult Hit;
	FCollisionShape const CapsuleShape = FCollisionShape::MakeCapsule(CapsuleComponent->GetScaledCapsuleRadius(), CapsuleComponent->GetScaledCapsuleHalfHeight());
	FRotator const Rotation = FRotator(GetActorRotation().Pitch, GetActorRotation().Yaw, GetActorRotation().Roll);
	GetWorld()->SweepSingleByChannel(Hit, GetActorLocation(),GetActorLocation(), Rotation.Quaternion(), ECC_Pawn, CapsuleShape);
	

	if (Hit.bBlockingHit && Hit.GetActor() && Hit.GetActor()->IsA(APlayerCharacter::StaticClass()))
	{
		// Damage player if hit
		UHealthComponent* HealthComp = Cast<UHealthComponent>(Hit.GetActor()->GetComponentByClass(UHealthComponent::StaticClass()));
		if (!HealthComp) return;

		HealthComp->TakeDamage(1, false);
	}
	
	Destroy();
}

