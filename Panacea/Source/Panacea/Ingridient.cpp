// Fill out your copyright notice in the Description page of Project Settings.


#include "Ingridient.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"

#include "Kismet/GameplayStatics.h"

// Sets default values
AIngridient::AIngridient()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//add tag Ingredient o the actor
	Tags.Add("Ingredient");



	//add switch camera component



}

// Called when the game starts or when spawned
void AIngridient::BeginPlay()
{
	Super::BeginPlay();

	TArray<UStaticMeshComponent*> Meshes;
	GetComponents<UStaticMeshComponent>(Meshes);
	if (Meshes.Num() > 0)
	{
		StaticMeshComponent = Meshes[0];
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Mesh Found: ") + GetActorLabel());
	}



}

// Called every frame
void AIngridient::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AIngridient::Interact()
{
	//call the switch camera component to switch the camera

}

void AIngridient::OnInteractableInRange()
{
	StaticMeshComponent->SetRenderCustomDepth(true);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("In Range:") + GetActorLabel());
}

void AIngridient::OnInteractableOutOfRange()
{
	StaticMeshComponent->SetRenderCustomDepth(false);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Out Of Range:") + GetActorLabel());
}

void AIngridient::SetMaterial(UMaterialInterface* NewMaterial)
{
	if (NewMaterial && StaticMeshComponent)
	{
		StaticMeshComponent->SetMaterial(0, NewMaterial); // 0 is the index for the first material slot
	}
}