// Richard Hill

#include "Boss_First_PhaseTwo.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/Engine.h"
#include "GP4/Enemies/AbilityComponents/Ability_SunBeams.h"
#include "GP4/Player/PlayerCharacter.h"

ABoss_First_PhaseTwo::ABoss_First_PhaseTwo()
{
	PrimaryActorTick.bCanEverTick = true;

	SunbeamComponent = CreateDefaultSubobject<UAbility_SunBeams>(TEXT("Sunbeam Ability Component"));
}

void ABoss_First_PhaseTwo::PerformAttack()
{
	Super::PerformAttack();

	if (SunbeamComponent)
	{
		SunbeamComponent->PerformAbility();
	}
}

void ABoss_First_PhaseTwo::BeginPlay()
{
	Super::BeginPlay();

	PlayerCharacter = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	
}

void ABoss_First_PhaseTwo::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
}


