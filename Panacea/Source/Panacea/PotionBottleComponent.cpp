// Fill out your copyright notice in the Description page of Project Settings.


#include "PotionBottleComponent.h"

// Sets default values for this component's properties
UPotionBottleComponent::UPotionBottleComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	OnDiaryReadDelegate.AddDynamic(this, &UPotionBottleComponent::SetInteractable);

	// ...
}


// Called when the game starts
void UPotionBottleComponent::BeginPlay()
{
	Super::BeginPlay();
	
}


// Called every frame
void UPotionBottleComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UPotionBottleComponent::Interact()
{
	if (!Interactable) {
		return;
	}

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Magenta, TEXT("Interacted With Potion bottle "));
}

void UPotionBottleComponent::Broadcast() {

}

