// Richard Hill

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Sunbeam.generated.h"

class UCapsuleComponent;

UCLASS()
class ASunbeam : public AActor
{
	GENERATED_BODY()

public:
	ASunbeam();

	UPROPERTY(EditAnywhere)
	UCapsuleComponent* CapsuleComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float DetonationTime = 3;

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	void CheckDetonationTime(float DeltaTime);
	void Detonate();
	
	float DetonationTimer = 0;
	bool bHasDetonated = false;
};
