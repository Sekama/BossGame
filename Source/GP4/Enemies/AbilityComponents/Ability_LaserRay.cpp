// Richard Hill


#include "Ability_LaserRay.h"
#include "GP4/Player/PlayerCharacter.h"
#include "Kismet/KismetMathLibrary.h"

UAbility_LaserRay::UAbility_LaserRay()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UAbility_LaserRay::PerformAbility()
{
	Super::PerformAbility();

	bAttackIsActive = true;
	AttackTimer = 0;

	if (LaserMesh)
	{
		LaserMesh->SetVisibility(true);
	}
}

void UAbility_LaserRay::BeginPlay()
{
	Super::BeginPlay();

	AttackTimer = AttackTime;

	// Initialize Static Mesh
	LaserMesh = Cast<UStaticMeshComponent>(GetOwner()->GetDefaultSubobjectByName(TEXT("Laser Mesh")));
	if (LaserMesh)
	{
		LaserMesh->SetVisibility(false);
	}
}

void UAbility_LaserRay::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	RotateTowardPlayer();
	CheckAttackTime(DeltaTime);
}

void UAbility_LaserRay::RotateTowardPlayer() const
{
	if (!bAttackIsActive) return;
	if (!PlayerCharacter) return;

	FVector const PlayerLocation = PlayerCharacter->GetActorLocation();

	FRotator const LookAtRotation = UKismetMathLibrary::FindLookAtRotation(GetOwner()->GetActorLocation(), PlayerLocation);
	FRotator const TargetRotation = FRotator(GetOwner()->GetActorRotation().Pitch, LookAtRotation.Yaw, GetOwner()->GetActorRotation().Roll);
	
	GetOwner()->SetActorRotation(TargetRotation);
}

void UAbility_LaserRay::CheckAttackTime(float DeltaTime)
{
	if (AttackTimer < AttackTime)
	{
		AttackTimer += DeltaTime;
	}
	else if (bAttackIsActive)
	{
		bAttackIsActive = false;
		if (LaserMesh)
		{
			LaserMesh->SetVisibility(false);
		}
	}
}

