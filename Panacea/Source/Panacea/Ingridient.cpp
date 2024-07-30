// Fill out your copyright notice in the Description page of Project Settings.


#include "Ingridient.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AIngridient::AIngridient()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//add tag Ingredient o the actor
	Tags.Add("Ingredient");

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	RootComponent = MeshComponent;



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
	SetMaterial(MaterialInRange);
	UE_LOG(	LogTemp, Warning, TEXT("OnInteractableInRange"));
}

void AIngridient::OnInteractableOutOfRange()
{
	SetMaterial(MaterialOutOfRange);
	UE_LOG(	LogTemp, Warning, TEXT("OnInteractableOutOfRange"));
}

void AIngridient::SetMaterial(UMaterialInterface* NewMaterial)
{
	if (NewMaterial && MeshComponent)
	{
		MeshComponent->SetMaterial(0, NewMaterial); // 0 is the index for the first material slot
	}
}