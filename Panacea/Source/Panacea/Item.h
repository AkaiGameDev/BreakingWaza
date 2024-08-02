// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Kismet/GameplayStatics.h"
#include "IInteractable.h"
#include "PanaceaGameMode.h"
#include "IInteractableItem.h"
#include "Item.generated.h"

UCLASS(ABSTRACT)
class PANACEA_API AItem : public AActor, public IIInteractableItem
{
	GENERATED_BODY()
	

public:	

	AItem() {
		
	}

	UPROPERTY(EditAnywhere)
		bool Interactable;

	UPROPERTY(EditAnywhere)
		FString InteractableTrigger;

	virtual void BeginPlay() override {
		Super::BeginPlay();

		/*APanaceaGameMode* GameMode = Cast<APanaceaGameMode>(UGameplayStatics::GetGameMode(GetWorld()));

		if (!GameMode)
		{
			UE_LOG(LogTemp, Warning, TEXT("GameMode is null"));
			return;
		}

		OnItemInteractedDelegate = &GameMode->OnItemInteractedDelegate;*/
	}

	virtual void Broadcast() override {
		

	}



	virtual void OnInteractableInRange() override {

		if (!Interactable) {
			return;
		}

		UStaticMeshComponent* mesh = GetComponentByClass<UStaticMeshComponent>();
		if (mesh) {
			mesh->SetRenderCustomDepth(true);
		}
	}
	virtual void OnInteractableOutOfRange() override {

		if (!Interactable) {
			return;
		}

		UStaticMeshComponent* mesh = GetComponentByClass<UStaticMeshComponent>();
		if (mesh) {
			mesh->SetRenderCustomDepth(false);
		}
	}

	virtual void Interact() override {

	}

	UFUNCTION()
	virtual void CheckInteractable(const FString& itemInteracted) override {
		UE_LOG(LogTemp, Warning, TEXT("Check interactable called by %s"), *itemInteracted);
		if (itemInteracted == InteractableTrigger) {
			SetInteractable();
		}
	}
	virtual void SetInteractable() override {
		UE_LOG(LogTemp, Warning, TEXT("Ingredient set interactable!!"));
		Interactable = true;
	}
	virtual void SetNotInteractable() override {
		Interactable = false;
	}

};
