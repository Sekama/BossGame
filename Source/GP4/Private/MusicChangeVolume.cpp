// Fill out your copyright notice in the Description page of Project Settings.


#include "MusicChangeVolume.h"

// Sets default values
AMusicChangeVolume::AMusicChangeVolume()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	SetRootComponent(Root);

	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger Box"));
	TriggerBox->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void AMusicChangeVolume::BeginPlay()
{
	Super::BeginPlay();
	
}