// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "MyBTTask_FindActorDistance.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class UBTTask_FindActorDistance : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTTask_FindActorDistance(FObjectInitializer const& ObjectInitializer);

private:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual FString GetStaticDescription() const override;
};

