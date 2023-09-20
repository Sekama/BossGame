// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BasePlatform.generated.h"

class APawn;
class UStaticMeshComponent;
class USceneComponent;
class UBoxComponent;

UCLASS(Abstract)
class ABasePlatform : public AActor
{
	GENERATED_BODY()
public:
	ABasePlatform();

	UPROPERTY(EditDefaultsOnly)
	USceneComponent* Root;
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* Mesh;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UBoxComponent* TriggerZone;
	UPROPERTY(EditAnywhere)
	bool PlayerSpecific = true;
	UPROPERTY(EditAnywhere)
	bool MovePlayer = true;
	
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex);

	UFUNCTION()
	virtual void OnBeginOverlap(AActor* OtherActor);
	UFUNCTION()
	virtual void OnEndOverlap(AActor* OtherActor);

	bool bActivated = false;
	UPROPERTY()
	APawn* PlayerRef;
};
