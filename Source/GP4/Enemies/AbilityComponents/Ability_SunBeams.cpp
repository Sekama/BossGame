// Richard Hill


#include "Ability_SunBeams.h"

#include "Components/CapsuleComponent.h"
#include "GP4/Enemies/BaseEnemy.h"
#include "GP4/Player/PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "GP4/Enemies/AbilityDependencies/Sunbeam.h"

UAbility_SunBeams::UAbility_SunBeams()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UAbility_SunBeams::PerformAbility()
{
	if (bOnCooldown) return;

	AttackTimer = 0;
	bOnCooldown = true;
	CooldownTimer = 0;
	bIsActive = true;
	GetWorld()->GetTimerManager().SetTimer(SpawnSunbeamTimerHandle, this, &UAbility_SunBeams::SpawnSunbeam, SpawnInterval, true);
	SpawnSunbeam();
}

void UAbility_SunBeams::BeginPlay()
{
	Super::BeginPlay();

	CooldownTimer = Cooldown;
	EnemyOwner = Cast<ABaseEnemy>(GetOwner());
	PlayerCharacter = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
}

void UAbility_SunBeams::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	CheckAttackTime(DeltaTime);
	CheckCooldown(DeltaTime);
}

void UAbility_SunBeams::CheckAttackTime(float DeltaTime)
{
	if (AttackTimer < AttackTime)
	{
		AttackTimer += DeltaTime;
	}
	else if (bIsActive)
	{
		bIsActive = false;
		GetWorld()->GetTimerManager().ClearTimer(SpawnSunbeamTimerHandle);
		UE_LOG(LogTemp,Warning,TEXT("Clear SunbeamSpawn timer"));
	}
}

void UAbility_SunBeams::CheckCooldown(float DeltaTime)
{
	if (CooldownTimer < Cooldown)
	{
		CooldownTimer += DeltaTime;
	}
	else if (bOnCooldown)
	{
		bOnCooldown = false;
	}
}

void UAbility_SunBeams::SpawnSunbeam() const
{
	if (!SunBeamClass) return;
	if (!PlayerCharacter) return;
	
	// SpawnLocation
	float const randomX = FMath::RandRange(-MaxRandomRangeFromPlayer, MaxRandomRangeFromPlayer);
	float const randomZ = FMath::RandRange(-MaxRandomRangeFromPlayer, MaxRandomRangeFromPlayer);
	FVector const RandomXZ = FVector(randomX, randomZ, -PlayerCharacter->Capsule->GetScaledCapsuleHalfHeight());
	FVector const SpawnLocation = PlayerCharacter->GetActorLocation() + RandomXZ;

	// SpawnParameters
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = GetOwner();
	SpawnParams.Instigator = GetOwner()->GetInstigator();

	// SpawnRotation
	FRotator const SpawnRotation = FRotator::ZeroRotator;

	// Spawn Sunbeam
	GetWorld()->SpawnActor<ASunbeam>(SunBeamClass, SpawnLocation, SpawnRotation, SpawnParams);
}

