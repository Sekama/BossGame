#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Triggerable.generated.h"

UCLASS()
class GP4_API ATriggerable : public AActor
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	ATriggerable();

	UFUNCTION(BlueprintCallable)
	virtual void Trigger();

	UFUNCTION(BlueprintImplementableEvent)
	void OnTrigger();

protected:
	UPROPERTY(BlueprintReadOnly)
	bool bIsTriggered = false;
	/* Should triggerable be able to be triggered endlessly? */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bEndlessTrigger = false;
};
