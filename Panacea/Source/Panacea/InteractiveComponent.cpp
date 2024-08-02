// Fill out your copyright notice in the Description page of Project Settings.

#include "InteractiveComponent.h"
#include "GameFramework/Actor.h"
#include "Components/CapsuleComponent.h"
#include "IInteractable.h"
#include "Components/StaticMeshComponent.h"
#include "DrawDebugHelpers.h"
#include "Engine/Engine.h"
#include "PanaceaCharacter.h"
#include "Blueprint/UserWidget.h"
#include "Camera/CameraComponent.h"  // Ensure this is included

UInteractiveComponent::UInteractiveComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	bIsHolding = false;
	bIsMovingToTarget = false;

	GrabbedActorLocationViewport = FVector(70.0f, 30.0f, -30.0f);

	MovementSpeed = 20.0f; // Units per second
	ReleaseDistance = 300.0f;

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
	UE_LOG(LogTemp, Warning, TEXT("UInteractiveComponent::BeginPlay - Start"));
	// Ensure that the Owner is set
	Owner = Cast<APanaceaCharacter>(GetOwner());

	if (!Owner)
	{
		UE_LOG(LogTemp, Error, TEXT("Owner is null."));
		return;
	}

	HintInteractionWidget = Owner->GetHintInteractionWidget();


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

	if (HintInteractionWidget)
	{
		HintInteractionWidget->SetVisibility(ESlateVisibility::Hidden);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("HintInteractionWidget is null in InteractiveComponent::BeginPlay"));
	}
}

void UInteractiveComponent::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	/*DrawDebugCapsuleVisualization();*/

	if (bIsMovingToTarget && ActorInFocus && ActorInFocusRootComponent) {

		FVector CurrentLocation;
		FRotator CurrentRotation;

		FVector DesiredLocation = bIsHolding ? TargetLocationToRelease : GrabbedActorLocationViewport;
		FRotator DesiredRotation = bIsHolding ? FRotator(0.0f, CurrentRotation.Yaw, CurrentRotation.Roll) : FRotator::ZeroRotator;

		if (!bIsHolding)
		{
			CurrentLocation = ActorInFocusRootComponent->GetRelativeLocation();
			FVector NewLocation = FMath::VInterpTo(CurrentLocation, DesiredLocation, DeltaTime, MovementSpeed);
			ActorInFocusRootComponent->SetRelativeLocation(NewLocation);

			CurrentRotation = ActorInFocusRootComponent->GetRelativeRotation();
			FRotator NewRotation = FMath::RInterpTo(CurrentRotation, DesiredRotation, DeltaTime, MovementSpeed);
			ActorInFocusRootComponent->SetRelativeRotation(NewRotation);
		}
		else
		{
			CurrentLocation = ActorInFocusRootComponent->GetComponentLocation();
			FVector NewLocation = FMath::VInterpTo(CurrentLocation, DesiredLocation, DeltaTime, MovementSpeed);
			ActorInFocusRootComponent->SetWorldLocation(NewLocation);

			CurrentRotation = ActorInFocusRootComponent->GetComponentRotation();
			FRotator NewRotation = FMath::RInterpTo(CurrentRotation, DesiredRotation, DeltaTime, MovementSpeed);
			ActorInFocusRootComponent->SetWorldRotation(NewRotation);
		}

		if (FVector::Dist(CurrentLocation, DesiredLocation) < 1.0f &&
			FQuat::Slerp(CurrentRotation.Quaternion(), DesiredRotation.Quaternion(), DeltaTime * MovementSpeed).Equals(DesiredRotation.Quaternion(), 1.0f))
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

	// Get the camera component from the owner
	UCameraComponent* CameraComponent = Owner->GetFirstPersonCameraComponent();
	if (!CameraComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("Camera component is null."));
		return nullptr;
	}

	FVector CameraLocation = CameraComponent->GetComponentLocation();

	// Iterate through the list of actors to find the closest one
	for (AActor* InteractableActor : ActorsToCheck)
	{
		if (InteractableActor)
		{
			FVector End = InteractableActor->GetActorLocation();
			FHitResult HitResult;

			FCollisionQueryParams QueryParams;
			QueryParams.AddIgnoredActor(Owner);
			QueryParams.AddIgnoredActor(InteractableActor); // Ignore the actor itself

			// Perform the line trace
			bool bHit = GetWorld()->LineTraceSingleByChannel(
				HitResult,
				CameraLocation,
				End,
				ECC_Visibility,
				QueryParams
			);

			// If the line trace doesn't hit anything, consider this actor
			if (!bHit)
			{
				float Distance = FVector::Dist(CameraLocation, End);
				if (Distance < ClosestDistance)
				{
					ClosestDistance = Distance;
					ClosestActor = InteractableActor;
				}
			}

			//// Debug drawing
			//DrawDebugLine(GetWorld(), CameraLocation, End, FColor::Green, false, 1.0f, 0, 1.0f);
			//if (bHit)
			//{
			//	DrawDebugPoint(GetWorld(), HitResult.Location, 10.0f, FColor::Red, false, 1.0f);
			//}
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

		if (bIsMovingToTarget)
			return;

		InteractableActors.AddUnique(OtherActor);

		// Get the closest actor to the owner
		AActor* NewActorInFocus = GetClosestToOwner(InteractableActors);
		if (ActorInFocus != NewActorInFocus)
		{
			// Notify the old actor that it is out of range
			if (ActorInFocusInteractableInterface)
			{
				ActorInFocusInteractableInterface->OnInteractableOutOfRange();
				HintInteractionWidget->SetVisibility(ESlateVisibility::Hidden);
			}

			SetActorInFocus(NewActorInFocus);

			// Notify the new actor that it is in range
			if (ActorInFocusInteractableInterface)
			{
				ActorInFocusInteractableInterface->OnInteractableInRange();
				HintInteractionWidget->SetVisibility(ESlateVisibility::Visible);

			}
		}
	}

	
}

void UInteractiveComponent::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

	if (IInteractable* Interactable = Cast<IInteractable>(OtherActor))
	{

		if (bIsMovingToTarget)
			return;


		InteractableActors.Remove(OtherActor);



		// If the actor going out of range was in focus, update the focus
		if (OtherActor == ActorInFocus)
		{
			if (IInteractable* OldInteractable = Cast<IInteractable>(ActorInFocus))
			{
				OldInteractable->OnInteractableOutOfRange();
				HintInteractionWidget->SetVisibility(ESlateVisibility::Hidden);
			}

			// Get the new closest actor to the owner
			SetActorInFocus(GetClosestToOwner(InteractableActors));

			// Notify the new actor that it is in range
			if (IInteractable* InteractableToCast = Cast<IInteractable>(ActorInFocus))
			{
				InteractableToCast->OnInteractableInRange();
				HintInteractionWidget->SetVisibility(ESlateVisibility::Visible);
			}
		}
	}
}

void UInteractiveComponent::Interact(const FInputActionValue& Value)
{
	if (ActorInFocus)
	{
		UE_LOG(LogTemp, Warning, TEXT("Works"));
		if (IInteractable* Interactable = Cast<IInteractable>(ActorInFocus))
		{
			if (!bIsHolding)
			{
				UE_LOG(LogTemp, Warning, TEXT("Works"));

				Grab();
			}
			else
				if (!bIsMovingToTarget)
					Release();
			/*Interactable->Interact();*/
		}
	}
}

void UInteractiveComponent::Grab()
{
	if (Owner && ActorInFocus)
	{
		UCameraComponent* CameraComponent = Owner->GetFirstPersonCameraComponent();
		if (CameraComponent)
		{
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

void UInteractiveComponent::Release()
{
	if (Owner && ActorInFocus && bIsHolding)
	{
		UCameraComponent* CameraComponent = Owner->GetFirstPersonCameraComponent();
		if (CameraComponent)
		{
			FVector CameraLocation = CameraComponent->GetComponentLocation();
			FVector CameraForward = CameraComponent->GetForwardVector();

			FVector BoxExtent(10.0f, 10.0f, 10.0f); // Define default the box extent for collision checking

			UStaticMeshComponent* MeshComponent = ActorInFocus->FindComponentByClass<UStaticMeshComponent>();
			if (MeshComponent)
			{
				FVector Origin, BoxBounds;
				MeshComponent->GetLocalBounds(Origin, BoxBounds);
				FVector ActorScale = MeshComponent->GetComponentScale();
				BoxExtent = BoxBounds * ActorScale; // Half size to get the box extent

			}

			FVector TraceEnd = CameraLocation + (CameraForward * ReleaseDistance);

			FCollisionQueryParams QueryParams;
			QueryParams.AddIgnoredActor(ActorInFocus);
			QueryParams.AddIgnoredActor(Owner);

			FHitResult HitResult;

			bool bHit = GetWorld()->LineTraceSingleByChannel(
				HitResult,
				CameraLocation,
				TraceEnd,
				ECC_Visibility,
				QueryParams
			);

			//// Debug drawing
			//DrawDebugLine(GetWorld(), CameraLocation, TraceEnd, FColor::Green, false, 1.0f, 0, 1.0f);
			//if (bHit)
			//{
			//	DrawDebugPoint(GetWorld(), HitResult.Location, 10.0f, FColor::Red, false, 1.0f);
			//}

			if (!bHit)
			{
				UE_LOG(LogTemp, Log, TEXT("Place to put object is not found."));
				return;
			}

			TargetLocationToRelease = HitResult.ImpactPoint + FVector::UpVector * (BoxExtent.X + 0.05f);

			if (IsPathClear(CameraLocation, TargetLocationToRelease, BoxExtent))
			{
				// Smoothly move the object to the target location
				if (ActorInFocusRootComponent)
				{
					ActorInFocusRootComponent->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
				}

				bIsMovingToTarget = true;

			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("Path is not clear, cannot release actor."));
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

	DrawDebugBox(GetWorld(), StartLocation, BoxExtent, FColor::Red, false, 1.0f);
	DrawDebugBox(GetWorld(), EndLocation, BoxExtent, FColor::Green, false, 1.0f);
	DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Blue, false, 1.0f, 0, 1.0f);

	if (HitResult.bBlockingHit)
		DrawDebugPoint(GetWorld(), HitResult.ImpactPoint, 10.0f, FColor::Red, false, 4.0f);


	return !bHit; // Return true if the path is clear
}

void UInteractiveComponent::OnMoveItemComplete()
{
	if (Owner && ActorInFocus)
	{
		if (!bIsHolding)
		{
			UCameraComponent* CameraComponent = Owner->GetFirstPersonCameraComponent();
			if (CameraComponent)
			{
				if (ActorInFocusRootComponent)
				{
					ActorInFocusRootComponent->AttachToComponent(CameraComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);


					if (ActorInFocusInteractableInterface)
					{
						ActorInFocusInteractableInterface->OnInteractableOutOfRange();
					}
				}
			}
		}
		else
		{
			if (ActorInFocusInteractableInterface)
			{
				ActorInFocusInteractableInterface->OnInteractableOutOfRange();
			}

			// Get the new closest actor to the owner
			SetActorInFocus(GetClosestToOwner(InteractableActors));

			// Notify the new actor that it is in range
			if (ActorInFocusInteractableInterface)
			{
				ActorInFocusInteractableInterface->OnInteractableInRange();
			}


		}
		bIsHolding = !bIsHolding;
	}
}

void UInteractiveComponent::SetActorInFocus(AActor* NewActorInFocus)
{
	ActorInFocus = NewActorInFocus;
	if (ActorInFocus)
	{
		ActorInFocusRootComponent = Cast<UPrimitiveComponent>(ActorInFocus->GetRootComponent());
		ActorInFocusInteractableInterface = Cast<IInteractable>(ActorInFocus);
	}
	else
	{
		ActorInFocusInteractableInterface = nullptr;
		ActorInFocusRootComponent = nullptr;
	}
}
