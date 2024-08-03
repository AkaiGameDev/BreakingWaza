#include "PotionBottle.h"

void APotionBottle::Interact()
{
	UE_LOG(LogTemp, Warning, TEXT("Potion bottle interact called"));
	if (Interactable) {
		UE_LOG(LogTemp, Warning, TEXT("Potion bottle interacted with"));
	}
}
