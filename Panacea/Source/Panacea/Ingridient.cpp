// Fill out your copyright notice in the Description page of Project Settings.


#include "Ingridient.h"

#include "Kismet/GameplayStatics.h"

// Sets default values
AIngridient::AIngridient()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//add tag Ingredient o the actor
	Tags.Add("Ingredient");

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Interacted With: ") +  GetActorLabel());
}

// Called when the game starts or when spawned
void AIngridient::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AIngridient::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AIngridient::Interact()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Interacted With: ") + GetActorLabel());
}

void AIngridient::OnInteractableInRange()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Interactable in range: ") + GetActorLabel());;
}

void AIngridient::OnInteractableOutOfRange()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Interactable out of range: ") + GetActorLabel());
}

