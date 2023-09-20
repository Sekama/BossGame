// Gabriel Ling Andersson

#include "Boss_First.h"
#include "GP4/Enemies/AbilityComponents/Ability_Stomp.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/Engine.h"
#include "GP4/Enemies/AbilityComponents/Ability_SunBeams.h"
#include "GP4/Player/PlayerCharacter.h"

ABoss_First::ABoss_First()
{
	PrimaryActorTick.bCanEverTick = true;

	StompComponent = CreateDefaultSubobject<UAbility_Stomp>(TEXT("Stomp Ability Component"));
	SunbeamComponent = CreateDefaultSubobject<UAbility_SunBeams>(TEXT("Sunbeam Ability Component"));

	//Sets Collision Box for Basic Attack
	AtColBox = CreateDefaultSubobject<UBoxComponent>(TEXT("AttackCollisionComponent"));
	AtColBox->SetCollisionProfileName(TEXT("Trigger"));
	AtColBox->SetupAttachment(RootComponent);
	
}

void ABoss_First::PerformAttack()
{
	Super::PerformAttack();
	/*if (StompComponent)
	{
		StompComponent->PerformAbility();
		//stomp_Anim = StompComponent->stomp_Anim;
	}*/

	if (SunbeamComponent)
	{
		SunbeamComponent->PerformAbility();
	}
}

void ABoss_First::BeginPlay()
{
	
	pInRange = false;
	
	Super::BeginPlay();

	PlayerCharacter = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	
}

void ABoss_First::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
}

void ABoss_First::ActivateCollider()
{
	UE_LOG(LogTemp,Warning,TEXT("Activate"));
}


