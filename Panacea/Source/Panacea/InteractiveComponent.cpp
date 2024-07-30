// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractiveComponent.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "IInteractable.h"
#include "DrawDebugHelpers.h"

UInteractiveComponent::UInteractiveComponent()
{

	PrimaryComponentTick.bCanEverTick = true;

	// Create and initialize the sphere component
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SphereComponent->InitSphereRadius(500.0f); // Set the radius for the sphere
	SphereComponent->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &UInteractiveComponent::OnOverlapBegin);
	SphereComponent->OnComponentEndOverlap.AddDynamic(this, &UInteractiveComponent::OnOverlapEnd);

	// Attach SphereComponent to RootComponent of the Actor
	if (USceneComponent* RootComp = GetOwner() ? GetOwner()->GetRootComponent() : nullptr)
	{
		SphereComponent->SetupAttachment(RootComp);
	}

	UE_LOG(LogTemp, Warning, TEXT("Interactive Component created"));
}


void UInteractiveComponent::BeginPlay()
{
	Super::BeginPlay();
	Owner = GetOwner();

	if (!Owner)
	{
		UE_LOG(LogTemp, Warning, TEXT("Owner not found"));
		return;
	}

	// Draw the sphere in the world for debugging purposes
	DrawDebugSphereVisualization();
}

void UInteractiveComponent::DrawDebugSphereVisualization() const
{
	if (AActor* OwnerActor = GetOwner())
	{
		FVector Location = OwnerActor->GetActorLocation() + SphereComponent->GetComponentLocation();
		float Radius = SphereComponent->GetScaledSphereRadius();
		DrawDebugSphere(GetWorld(), Location, Radius, 12, FColor::Red, false, -1, 0, 1);
	}
}

void UInteractiveComponent::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IInteractable* Interactable = Cast<IInteractable>(OtherActor))
	{
		InteractableActors.AddUnique(OtherActor);
		Interactable->OnInteractableInRange();
		UE_LOG(LogTemp, Warning, TEXT("Interactable actor detected: %s"), *OtherActor->GetName());
	}
}

void UInteractiveComponent::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (IInteractable* Interactable = Cast<IInteractable>(OtherActor))
	{
		InteractableActors.Remove(OtherActor);
		Interactable->OnInteractableOutOfRange();
		UE_LOG(LogTemp, Warning, TEXT("Interactable actor out of range: %s"), *OtherActor->GetName());
	}
}


void UInteractiveComponent::Interact(const FInputActionValue& Value)
{
	if (InteractableActors.Num() > 0)
	{
		// Interact with the first actor in the list for simplicity
		AActor* ActorToInteract = InteractableActors[0];
		IInteractable* Interactable = Cast<IInteractable>(ActorToInteract);
		if (Interactable)
		{
			Interactable->Interact();
			UE_LOG(LogTemp, Warning, TEXT("Interacting with actor: %s"), *ActorToInteract->GetName());
		}
	}
}

