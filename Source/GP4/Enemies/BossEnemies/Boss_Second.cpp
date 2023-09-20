// Richard Hill

#include "Boss_Second.h"

#include "GP4/Enemies/AbilityComponents/Ability_LaserRay.h"
#include "GP4/Enemies/AbilityComponents/BaseAbilityComponent.h"
#include "GP4/Player/PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

ABoss_Second::ABoss_Second()
{
	PrimaryActorTick.bCanEverTick = true;

	LaserRayComponent = CreateDefaultSubobject<UAbility_LaserRay>(TEXT("Laser Ray Ability Component"));
}

void ABoss_Second::PerformAttack()
{
	Super::PerformAttack();

	LaserRayComponent->PerformAbility();
}

void ABoss_Second::BeginPlay()
{
	Super::BeginPlay();
	Player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
}

void ABoss_Second::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABoss_Second::RotateTowardPlayer()
{
	if (!Player) return;
	
	FVector const PlayerLocation = Player->GetActorLocation();

	FRotator const LookAtRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), PlayerLocation);
	FRotator const TargetRotation = FRotator(GetActorRotation().Pitch, LookAtRotation.Yaw, GetActorRotation().Roll);
	
	SetActorRotation(TargetRotation);
}

FVector ABoss_Second::UpdatePID(const FVector& InError, float InDeltaTime)
{
	if (InDeltaTime <= 0.f || InError.ContainsNaN())
	{
		return FVector::ZeroVector;
	}

	// Proportional
	const FVector POut = Proportion * InError;

	// Integral
	FVector const IntegralError = InDeltaTime * InError;
	FVector const IOut = Integral * IntegralError;

	// Derivative
	FVector const DerivativeError = (InError - PrevError) / InDeltaTime;
	FVector const DOut = Derivative * DerivativeError;

	// Set LastError
	PrevError = InError;

	// Calculate Output
	const FVector Output = POut + IOut + DOut;

	return Output.BoundToCube(MaxOutput);
	
}

float ABoss_Second::ResetPID(float NewErrorValue, float NewAccumulatorValue)
{
	LastError = NewErrorValue;
	Accumulator = NewAccumulatorValue;
	return 0;
}

