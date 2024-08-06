// Fill out your copyright notice in the Description page of Project Settings.


#include "KeyActor.h"
#include "GameFramework/Character.h" 
#include "InteractiveComponent.h"

void AKeyActor::Interact()
{
	FirstInteraction();


	bool bIsChestOverlapping = false;

	ACharacter* Character = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	TArray<AActor*> OverlappingActors;
	Character->GetOverlappingActors(OverlappingActors);

	for (AActor* Actor : OverlappingActors)
	{
		if (Actor->ActorHasTag("Chest"))
		{
			bIsChestOverlapping = true;
		}
	}

	if (bIsChestOverlapping)
	{
		Broadcast();

		UInteractiveComponent* InteractiveComponent = Character->GetComponentByClass<UInteractiveComponent>();
		if (InteractiveComponent)
		{
			InteractiveComponent->SetAndStartMovement(ChestLockLocation, ChestLockRotation, true);
			SetNotInteractable();
		}
	}
}
