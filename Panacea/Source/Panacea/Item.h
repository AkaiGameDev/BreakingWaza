// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "IInteractable.h"
#include "IInteractableItem.h"
#include "Item.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnItemInteracted, FString, ItemName);

UCLASS(ABSTRACT)
class PANACEA_API UItem : public UActorComponent, public IIInteractableItem
{
	GENERATED_BODY()
	

public:	

	UItem() {

	}

	UPROPERTY(EditAnywhere)
		bool Interactable;

	UPROPERTY(EditAnywhere)
		FString InteractableTrigger;

	UPROPERTY(BlueprintAssignable)
		FOnItemInteracted OnItemInteractedDelegate;

	virtual void Broadcast() override {

	}

	virtual void OnInteractableInRange() override {

		if (!Interactable) {
			return;
		}

		UStaticMeshComponent* mesh = GetOwner()->GetComponentByClass<UStaticMeshComponent>();
		if (mesh) {
			mesh->SetRenderCustomDepth(true);
		}
	}
	virtual void OnInteractableOutOfRange() override {

		if (!Interactable) {
			return;
		}

		UStaticMeshComponent* mesh = GetOwner()->GetComponentByClass<UStaticMeshComponent>();
		if (mesh) {
			mesh->SetRenderCustomDepth(false);
		}
	}

	virtual void Interact() override {

	}

	UFUNCTION()
	virtual void CheckInteractable(FString itemInteracted) override {
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
