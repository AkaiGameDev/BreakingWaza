// Fill out your copyright notice in the Description page of Project Settings.

#include "InteractiveComponent.h"
#include "GameFramework/Actor.h"
#include "Components/CapsuleComponent.h"
#include "IInteractable.h"
#include "Components/StaticMeshComponent.h"
#include "DrawDebugHelpers.h"
#include "Engine/Engine.h"
#include "PanaceaCharacter.h"
#include "Camera/CameraComponent.h"  // Ensure this is included

UInteractiveComponent::UInteractiveComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	bIsHolding = false;

	// Create and initialize the capsule component
	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	CapsuleComponent->InitCapsuleSize(20.0f, 170.0f); // Set the radius and half-height for the capsule
	CapsuleComponent->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	CapsuleComponent->SetVisibility(true);

	// Bind the overlap events
	CapsuleComponent->OnComponentBeginOverlap.AddDynamic(this, &UInteractiveComponent::OnOverlapBegin);
	CapsuleComponent->OnComponentEndOverlap.AddDynamic(this, &UInteractiveComponent::OnOverlapEnd);
}

void UInteractiveComponent::BeginPlay()
{
	Super::BeginPlay();

	// Ensure that the Owner is set
	Owner = Cast<APanaceaCharacter>(GetOwner());

	if (!Owner)
	{
		UE_LOG(LogTemp, Error, TEXT("Owner is null."));
		return;
	}

	UCameraComponent* CameraComponent = Owner->GetFirstPersonCameraComponent();
	if (!CameraComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("Camera component is null."));
		return;
	}

	// Cast UCameraComponent to USceneComponent
	USceneComponent* RootComp = Cast<USceneComponent>(CameraComponent);
	if (!RootComp)
	{
		UE_LOG(LogTemp, Error, TEXT("Casting to USceneComponent failed."));
		return;
	}

	CapsuleComponent->AttachToComponent(RootComp, FAttachmentTransformRules::KeepRelativeTransform);
	CapsuleComponent->SetRelativeLocation(FVector::ForwardVector * 100.0f);
	CapsuleComponent->SetRelativeRotation(FRotator(90.0f, 0.0f, 0.0f));
}

void UInteractiveComponent::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	/*DrawDebugCapsuleVisualization();*/

	if (bIsMovingToTarget && ActorInFocus && ActorInFocusRootComponent)
	{
		FVector CurrentLocation = ActorInFocusRootComponent->GetRelativeLocation();
		FVector NewLocation = FMath::VInterpTo(CurrentLocation, GrabbedActorLocationViewport, DeltaTime, MovementSpeed);
		ActorInFocusRootComponent->SetRelativeLocation(NewLocation);

		if (FVector::Dist(CurrentLocation, GrabbedActorLocationViewport) < 1.0f)
		{
			bIsMovingToTarget = false;
			UE_LOG(LogTemp, Warning, TEXT("Actor in focus reached target location."));
			OnMoveItemComplete();
		}
	}
}

void UInteractiveComponent::DrawDebugCapsuleVisualization() const
{
	if (AActor* OwnerActor = GetOwner())
	{
		FVector Location = CapsuleComponent->GetComponentLocation();
		float HalfHeight = CapsuleComponent->GetScaledCapsuleHalfHeight();
		float Radius = CapsuleComponent->GetScaledCapsuleRadius();
		FQuat Rotation = CapsuleComponent->GetComponentQuat();
		DrawDebugCapsule(GetWorld(), Location, HalfHeight, Radius, Rotation, FColor::Red, false, -1, 0, 0.3);
	}
}

AActor* UInteractiveComponent::GetClosestToOwner(const TArray<AActor*>& ActorsToCheck)
{
	AActor* ClosestActor = nullptr;
	float ClosestDistance = FLT_MAX;

	// Iterate through the list of actors to find the closest one
	for (AActor* InteractableActor : ActorsToCheck)
	{
		if (InteractableActor)
		{
			float Distance = FVector::Dist(Owner->GetActorLocation(), InteractableActor->GetActorLocation());
			if (Distance < ClosestDistance)
			{
				ClosestDistance = Distance;
				ClosestActor = InteractableActor;
			}
		}
	}

	return ClosestActor;
}

void UInteractiveComponent::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	const FHitResult& SweepResult)
{


	if (Cast<IInteractable>(OtherActor) != nullptr)
	{
		InteractableActors.AddUnique(OtherActor);

		if (bIsHolding)
			return;


		// Get the closest actor to the owner
		AActor* NewActorInFocus = GetClosestToOwner(InteractableActors);
		if (ActorInFocus != NewActorInFocus)
		{
			// Notify the old actor that it is out of range
			if (IInteractable* OldInteractable = Cast<IInteractable>(ActorInFocus))
			{
				OldInteractable->OnInteractableOutOfRange();
			}

			SetActorInFocus(NewActorInFocus);

			// Notify the new actor that it is in range
			if (IInteractable* NewInteractable = Cast<IInteractable>(ActorInFocus))
			{
				NewInteractable->OnInteractableInRange();
			}
		}
	}
}

void UInteractiveComponent::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

	if (IInteractable* Interactable = Cast<IInteractable>(OtherActor))
	{

		InteractableActors.Remove(OtherActor);

		if (bIsHolding)
			return;


		// If the actor going out of range was in focus, update the focus
		if (OtherActor == ActorInFocus)
		{
			if (IInteractable* OldInteractable = Cast<IInteractable>(ActorInFocus))
			{
				OldInteractable->OnInteractableOutOfRange();
			}

			// Get the new closest actor to the owner
			SetActorInFocus(GetClosestToOwner(InteractableActors));

			// Notify the new actor that it is in range
			if (IInteractable* InteractableToCast = Cast<IInteractable>(ActorInFocus))
			{
				InteractableToCast->OnInteractableInRange();
			}
		}
	}
}

void UInteractiveComponent::Interact(const FInputActionValue& Value)
{
	if (!bIsHolding && ActorInFocus)
	{
		if (IInteractable* Interactable = Cast<IInteractable>(ActorInFocus))
		{

			Grab();
			/*Interactable->Interact();*/
		}
	}
}

void UInteractiveComponent::Grab()
{
	if (Owner && ActorInFocus)
	{
		UE_LOG(LogTemp, Warning, TEXT("Works1"));

		UCameraComponent* CameraComponent = Owner->GetFirstPersonCameraComponent();
		if (CameraComponent)
		{
			UE_LOG(LogTemp, Warning, TEXT("Works2"));

			// Attach the root component of the actor in focus to the camera component
			UPrimitiveComponent* ActorRootComponent = Cast<UPrimitiveComponent>(ActorInFocus->GetRootComponent());
			if (ActorRootComponent)
			{
				ActorRootComponent->AttachToComponent(CameraComponent, FAttachmentTransformRules::KeepWorldTransform);
				bIsMovingToTarget = true;
				UE_LOG(LogTemp, Warning, TEXT("Actor in focus grabbed and moving started."));
			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT("Actor in focus root component is null."));
			}
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Camera component is null."));
		}
	}
}

bool UInteractiveComponent::IsPathClear(const FVector& StartLocation, const FVector& EndLocation, const FVector& BoxExtent) const
{
	FCollisionShape Box = FCollisionShape::MakeBox(BoxExtent);
	FHitResult HitResult;

	// Perform the box trace
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(ActorInFocus);
	QueryParams.AddIgnoredActor(Owner);

	// Perform the box trace
	bool bHit = GetWorld()->SweepSingleByChannel(
		HitResult,
		StartLocation,
		EndLocation,
		FQuat::Identity,
		ECC_Visibility,
		Box,
		QueryParams
	);

#if UE_BUILD_DEBUG
	DrawDebugBox(GetWorld(), StartLocation, BoxExtent, FColor::Red, false, 1.0f);
	DrawDebugBox(GetWorld(), EndLocation, BoxExtent, FColor::Green, false, 1.0f);
	DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Blue, false, 1.0f, 0, 1.0f);
#endif

	if (HitResult.bBlockingHit)
		UE_LOG(LogTemp, Warning, TEXT("Something is blocking box trace"))


		return !bHit; // Return true if the path is clear
}

void UInteractiveComponent::OnMoveItemComplete()
{
	if (Owner && ActorInFocus)
	{
		UCameraComponent* CameraComponent = Owner->GetFirstPersonCameraComponent();
		if (CameraComponent)
		{
			UPrimitiveComponent* ActorRootComponent = Cast<UPrimitiveComponent>(ActorInFocus->GetRootComponent());
			if (ActorRootComponent)
			{
				ActorRootComponent->AttachToComponent(CameraComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
			
				if (IInteractable* OldInteractable = Cast<IInteractable>(ActorInFocus))
				{
					OldInteractable->OnInteractableOutOfRange();
				}
			}
		}
	}
}

void UInteractiveComponent::SetActorInFocus(AActor* NewActorInFocus)
{
	ActorInFocus = NewActorInFocus;
	if (ActorInFocus)
	{
		ActorInFocusRootComponent = Cast<UPrimitiveComponent>(ActorInFocus->GetRootComponent());
	}
	else
	{
		ActorInFocusRootComponent = nullptr;
	}
}
