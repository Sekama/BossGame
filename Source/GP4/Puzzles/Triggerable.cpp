#include "Triggerable.h"

// Sets default values
ATriggerable::ATriggerable()
{
	// Set this actor to call Tick() every frame. You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

/**
 * @brief Triggers the triggerable object.
 */
void ATriggerable::Trigger()
{
	if(bIsTriggered && !bEndlessTrigger) return;

	bIsTriggered = true;
	OnTrigger();
}