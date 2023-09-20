// Richard Hill


#include "BaseAbilityComponent.h"

#include "GP4/Enemies/BaseEnemy.h"
#include "GP4/Player/PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"

UBaseAbilityComponent::UBaseAbilityComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UBaseAbilityComponent::PerformAbility()
{
	
}

void UBaseAbilityComponent::BeginPlay()
{
	Super::BeginPlay();
	
	EnemyOwner = Cast<ABaseEnemy>(GetOwner());
	PlayerCharacter = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
}

void UBaseAbilityComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
}

