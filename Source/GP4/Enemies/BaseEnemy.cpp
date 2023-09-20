// Richard Hill


#include "BaseEnemy.h"

#include "CustomAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GP4/CustomComponents/Health/HealthComponent.h"

ABaseEnemy::ABaseEnemy()
{
	PrimaryActorTick.bCanEverTick = true;

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health Component"));
}


float ABaseEnemy::GetAttackTime()
{
	return AttackTime;
}

void ABaseEnemy::SetDeathMaterialFade(float DeltaTime)
{	
	if (!bPlayDeathMaterialFade) return;
	
	float const CurrentAlpha = DynamicMaterial->K2_GetScalarParameterValue(TEXT("AnimAlpha"));

	if (bPlayReviveMaterialFade)
	{
		float const ReviveFadeAlpha = FMath::FInterpConstantTo(CurrentAlpha, 0, DeltaTime, DeathMaterialFadeInterpSpeed);
		DynamicMaterial->SetScalarParameterValue(TEXT("AnimAlpha"), ReviveFadeAlpha);
		
		if (ReviveFadeAlpha <= 0)
		{
			bPlayReviveMaterialFade = false;
			bPlayDeathMaterialFade = false;
		}
	}
	else
	{
		float const FadeAlpha = FMath::FInterpConstantTo(CurrentAlpha, 1, DeltaTime, DeathMaterialFadeInterpSpeed);
		DynamicMaterial->SetScalarParameterValue(TEXT("AnimAlpha"), FadeAlpha);
		
		if (FadeAlpha >= 1) // Disable enemy
		{
			SetActorHiddenInGame(true);
			SetActorTickEnabled(false);
			AggroTarget(false);
			FTimerHandle Timer;
			GetWorldTimerManager().SetTimer(Timer, this, &ABaseEnemy::SpawnEnemy, RespawnTime);
		}
	}
}

void ABaseEnemy::PerformAttack()
{
	
}

void ABaseEnemy::OnHit(float Damage, bool IsCrit)
{
	if (HealthComponent->GetIsDead()) return;
	if (!bHasAggro)
	{
		AggroTarget(true);
	}
	
	// Play Random Hit Animation Montage
	if (!HitMontage) return;
	int const Sections = HitMontage->GetNumSections();
	int const Random = FMath::RandRange(0, Sections - 1);
	FName const StartSectionName = HitMontage->GetSectionName(Random);
	PlayAnimationMontage(HitMontage, 1, StartSectionName);
}

void ABaseEnemy::TriggerDeath()
{
	AIController->UnPossess();
	SetActorEnableCollision(false);
	
	PlayAnimationMontage(DeathMontage);
}

void ABaseEnemy::StartDeathMaterialFade()
{
	bPlayDeathMaterialFade = true;
}

void ABaseEnemy::AggroTarget(bool HasAggro)
{
	bHasAggro = HasAggro;
	AIController->GetBlackboardComponent()->SetValueAsBool(FName(TEXT("HasAggro")), HasAggro);
}

void ABaseEnemy::DisableEnemy()
{
	bPlayDeathMaterialFade = true;
	UCapsuleComponent* Capsule = GetCapsuleComponent();
	SetActorEnableCollision(false);
}

void ABaseEnemy::BeginPlay()
{
	Super::BeginPlay();

	SpawnLocation = GetActorLocation();

	

	// Set Dynamic Material for Death Material Fade
	UMaterialInterface* MaterialInstance = GetMesh()->GetMaterial(0);
	DynamicMaterial = UMaterialInstanceDynamic::Create(MaterialInstance, this);
	GetMesh()->SetMaterial(0, DynamicMaterial);

	AIController = Cast<ACustomAIController>(GetController());
	if (AIController)
	{
		AIController->SetBehaviorTree(BehaviorTree);
		AIController->GetBlackboard()->SetValueAsVector("SpawnPoint", SpawnLocation);
	}
}

void ABaseEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SetDeathMaterialFade(DeltaTime);
}

float ABaseEnemy::PlayAnimationMontage(UAnimMontage* Montage, float InPlayRate, FName StartSectionName, float StartMontageAt)
{
	USkeletalMeshComponent* SkeletalMesh = GetMesh();
	UAnimInstance* AnimInstance = (SkeletalMesh)? SkeletalMesh->GetAnimInstance() : nullptr; 
	if ( Montage && AnimInstance )
	{
		float Duration = AnimInstance->Montage_Play(Montage, InPlayRate, EMontagePlayReturnType::MontageLength, StartMontageAt);
		if (Duration > 0.f)
		{
			// Start at a given Section.
			if( StartSectionName != NAME_None )
			{
				AnimInstance->Montage_JumpToSection(StartSectionName, Montage);
				int const MontageSectionID = Montage->GetSectionIndex(StartSectionName);
				Duration = Montage->GetSectionLength(MontageSectionID);
			}
			float const DurationModified = (Duration * InPlayRate) - Duration;
			float const ReturnDuration = FMath::Abs(Duration - DurationModified);
			return ReturnDuration;
		}
	}
	return 0;
}

void ABaseEnemy::Destroyed()
{
	Super::Destroyed();

	TArray<AActor*> AttachedActors;
	GetAttachedActors(AttachedActors);

	if (AttachedActors.Num() > 0)
	{
		for (AActor* AttachedActor : AttachedActors)
		{
			AttachedActor->Destroy();
		}
	}
}

void ABaseEnemy::SpawnEnemy()
{
	SetActorLocation(SpawnLocation);
	SetActorHiddenInGame(false);
	SetActorTickEnabled(true);
	SetActorEnableCollision(true);
	
	HealthComponent->GainHealth(HealthComponent->MaxHealth);
	HealthComponent->SetIsDead(false);
	
	bPlayReviveMaterialFade = true;
	bPlayDeathMaterialFade = true;
	
	bHasAggro = false;

	AIController->Possess(this);
	AIController->RunBehaviorTree(BehaviorTree);
	AIController->SetFocus(nullptr);
}
