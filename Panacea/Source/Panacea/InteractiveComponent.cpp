// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractiveComponent.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "IInteractable.h"
#include "Components/StaticMeshComponent.h"
#include "DrawDebugHelpers.h"
#include "Engine/Engine.h"

UInteractiveComponent::UInteractiveComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	// Create and initialize the sphere component
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SphereComponent->InitSphereRadius(150.0f); // Set the radius for the sphere
	SphereComponent->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	SphereComponent->SetVisibility(true);

	// Bind the overlap events
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &UInteractiveComponent::OnOverlapBegin);
	SphereComponent->OnComponentEndOverlap.AddDynamic(this, &UInteractiveComponent::OnOverlapEnd);
}

void UInteractiveComponent::BeginPlay()
{
	Super::BeginPlay();

	// Ensure that the Owner is set
	Owner = GetOwner();

	// Attach SphereComponent to RootComponent of the Actor
	if (Owner)
	{
		if (USceneComponent* RootComp = Owner->GetRootComponent())
		{
			SphereComponent->AttachToComponent(RootComp, FAttachmentTransformRules::KeepRelativeTransform);
			SphereComponent->SetRelativeLocation(FVector::ForwardVector * 150.0f); // Ensure it's at the root's location
			UE_LOG(LogTemp, Warning, TEXT("SphereComponent attached successfully."));
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Root component is null."));
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Owner is null."));
	}
}

void UInteractiveComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                          FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	//DrawDebugSphereVisualization();
}

void UInteractiveComponent::DrawDebugSphereVisualization() const
{
	if (AActor* OwnerActor = GetOwner())
	{
		FVector Location = SphereComponent->GetComponentLocation();
		float Radius = SphereComponent->GetScaledSphereRadius();
		DrawDebugSphere(GetWorld(), Location, Radius, 12, FColor::Red, false, -1, 0, 0.3);
	}

}

void UInteractiveComponent::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                           UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                           const FHitResult& SweepResult)
{
	if (IInteractable* Interactable = Cast<IInteractable>(OtherActor))
	{
		InteractableActors.AddUnique(OtherActor);
		Interactable->OnInteractableInRange();
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Interactable actor in range"));
	}
}

void UInteractiveComponent::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                         UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (IInteractable* Interactable = Cast<IInteractable>(OtherActor))
	{
		InteractableActors.Remove(OtherActor);
		Interactable->OnInteractableOutOfRange();
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Interactable actor out of range"));
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
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Interacting with actor"));
		}
	}
}
