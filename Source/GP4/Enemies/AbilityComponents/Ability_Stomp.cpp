// Richard Hill


#include "Ability_Stomp.h"

#include "Components/BoxComponent.h"
#include "GP4/CustomComponents/Health/HealthComponent.h"
#include "GP4/Enemies/BaseEnemy.h"
#include "GP4/Enemies/BossEnemies/Boss_First.h"
#include "GP4/Player/PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"

UAbility_Stomp::UAbility_Stomp()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UAbility_Stomp::PerformAbility()
{
	UE_LOG(LogTemp,Warning,TEXT("PERFORMING ATTACK"));
	
	stomp_Anim = true;
		
	// Collider->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	// Collider->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	/*if (AttackTimer >= AttackTime)
	{
		UE_LOG(LogTemp,Warning,TEXT("PERFORMING ATTACK"));
		
		GetOwner()->AddActorLocalOffset(FVector(0,0, 100));
		// AttackVisual->SetVisibility(true);
		
		AttackTimer = 0;
		bAttackActive = true;
		
		// Collider->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		// Collider->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		
	}*/
}

void UAbility_Stomp::BeginPlay()
{
	Super::BeginPlay();
	
	AttackTimer = AttackTime;
	
	EnemyOwner = Cast<ABaseEnemy>(GetOwner());
	PlayerCharacter = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));


	AttackVisual = Cast<UStaticMeshComponent>(GetOwner()->GetDefaultSubobjectByName(TEXT("AttackVisual")));
	//CollisionBox = Cast<UBoxComponent>(GetOwner()->GetDefaultSubobjectByName(TEXT("AttackCollisionComponent")));
	
	if (AttackVisual)
	{
		AttackVisual->SetVisibility(false);
	}
}

void UAbility_Stomp::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	//CheckAttackTime(DeltaTime);

	
}

void UAbility_Stomp::CheckAttackTime(float DeltaTime)
{
	//UE_LOG(LogTemp,Warning,TEXT("Attacktime is: %f"), AttackTimer);
	if (AttackTimer < AttackTime)
	{
		AttackTimer += DeltaTime;
	}
	else if (bAttackActive)
	{
		bAttackActive = false;
		AttackVisual->SetVisibility(false);
		//CollisionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}

