// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractiveComponent.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "IInteractable.h"
#include "Components/StaticMeshComponent.h"
#include "DrawDebugHelpers.h"

UInteractiveComponent::UInteractiveComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	// Create and initialize the sphere component
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SphereComponent->InitSphereRadius(100.0f); // Set the radius for the sphere
	SphereComponent->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &UInteractiveComponent::OnOverlapBegin);
	SphereComponent->OnComponentEndOverlap.AddDynamic(this, &UInteractiveComponent::OnOverlapEnd);

	SphereComponent->SetVisibility(true);
}


void UInteractiveComponent::BeginPlay()
{
	Super::BeginPlay();
	Owner = GetOwner();

	// Attach SphereComponent to RootComponent of the Actor
	if (USceneComponent* RootComp = GetOwner() ? GetOwner()->GetRootComponent() : nullptr)
	{
		SphereComponent->SetWorldLocation(GetOwner()->GetActorLocation());
		SphereComponent->SetupAttachment(RootComp);
		UE_LOG(LogTemp, Warning, TEXT("works"));
	}
}

void UInteractiveComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                          FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (AActor* OwnerActor = GetOwner())
	{
		FVector ForwardDirection = OwnerActor->GetActorForwardVector();
		FVector FrontOffset = ForwardDirection * 100.0f; // Adjusted to 100 units in front of the actor
		FVector NewLocation = OwnerActor->GetActorLocation() + FrontOffset;


		SphereComponent->SetWorldLocation(NewLocation);
	}

	DrawDebugSphereVisualization();
}

void UInteractiveComponent::DrawDebugSphereVisualization() const
{
	if (AActor* OwnerActor = GetOwner())
	{
		FVector Location = SphereComponent->GetComponentLocation();
		float Radius = SphereComponent->GetScaledSphereRadius();
		DrawDebugSphere(GetWorld(), Location, Radius, 12, FColor::Red, false, -1, 0, 0.3);
	}

	//UE_LOG(LogTemp, Warning, TEXT("%f, %f, %f"), SphereComponent->GetComponentLocation().X, SphereComponent->GetComponentLocation().Y, SphereComponent->GetComponentLocation().Z);
	UE_LOG(LogTemp, Warning, TEXT("%f, %f, %f"), GetOwner()->GetActorLocation().X, GetOwner()->GetActorLocation().Y,
	       GetOwner()->GetActorLocation().Z);
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
