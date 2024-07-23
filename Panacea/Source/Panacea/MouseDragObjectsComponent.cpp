// Fill out your copyright notice in the Description page of Project Settings.


#include "MouseDragObjectsComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "DrawDebugHelpers.h" // For debugging purposes
#include "CollisionQueryParams.h"

// Sets default values for this component's properties
UMouseDragObjectsComponent::UMouseDragObjectsComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	bIsGrabMode = false;

	PhysicsHandle = CreateDefaultSubobject<UPhysicsHandleComponent>(TEXT("PhysicsHandle"));
}

void UMouseDragObjectsComponent::SetInitilizeReferences()
{
	Character = Cast<APanaceaCharacter>(GetOwner());
	if (!Character)
	{
		UE_LOG(LogTemp, Error, TEXT("An error has been encountered in the UMouseDragObjectsComponent::SetInitialiseReferences() method: Owner is not of class APanaceaCharacter "));
		return;
	}
}

// Called when the game starts
void UMouseDragObjectsComponent::BeginPlay()
{
	Super::BeginPlay();


	PlayerController = Cast<APlayerController>(Character->GetController());
	if (PlayerController)
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(MouseDragObjectsMappingContext, 1);
			if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerController->InputComponent))
			{
				EnhancedInputComponent->BindAction(GrabModeAction, ETriggerEvent::Triggered, this, &UMouseDragObjectsComponent::SwitchGrabMode);
				EnhancedInputComponent->BindAction(GrabObjectAction, ETriggerEvent::Started, this, &UMouseDragObjectsComponent::GrabComponent);
				EnhancedInputComponent->BindAction(GrabObjectAction, ETriggerEvent::Completed, this, &UMouseDragObjectsComponent::ReleaseComponent);
			}
		}
	}

}


// Called every frame
void UMouseDragObjectsComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!bIsGrabMode)
	{
		return;
	}

	if (!GrabbedComponent || !GrabbedComponent->IsSimulatingPhysics())
	{
		return;
	}

	FVector WorldPosition;
	FVector WorldDirection;

	PlayerController->DeprojectMousePositionToWorld(WorldPosition, WorldDirection);

	if (WorldPosition.IsNearlyZero())
	{
		return;
	}

	FVector TargetLocation = WorldPosition + WorldDirection * OriginalDistanceToComponent;

	PhysicsHandle->SetTargetLocation(TargetLocation);

	/*APlayerCameraManager* CameraManager = PlayerController->PlayerCameraManager;
	if (!CameraManager)
	{
		return;
	}

	FVector Position;
	FVector Direction;

	PlayerController->DeprojectMousePositionToWorld(Position, Direction);*/

	UE_LOG(LogTemp, Log, TEXT("Position: X=%f, Y=%f, Z=%f"), WorldPosition.X, WorldPosition.Y, WorldPosition.Z);

}


void UMouseDragObjectsComponent::SwitchGrabMode()
{
	bIsGrabMode = !bIsGrabMode;
	if (bIsGrabMode)
	{
		// Set input mode to UI and Game
		FInputModeGameAndUI InputMode;
		InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
		InputMode.SetHideCursorDuringCapture(false);
		PlayerController->SetInputMode(InputMode);

		// Show the mouse cursor
		PlayerController->bShowMouseCursor = true;

		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->RemoveMappingContext(DefaultMappingContext);
		}


	}
	else
	{
		// Set input mode to Game only
		FInputModeGameOnly InputMode;
		PlayerController->SetInputMode(InputMode);
		// Hide the mouse cursor
		PlayerController->bShowMouseCursor = false;


		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

UPrimitiveComponent* UMouseDragObjectsComponent::FindComponent(FHitResult& HitResult)
{

	FVector WorldPosition;
	FVector WorldDirection;

	PlayerController->DeprojectMousePositionToWorld(WorldPosition, WorldDirection);


	// Get the world from the actor
	UWorld* World = GetWorld();
	if (!World)	return nullptr;

	// Define start and end points for the line trace
	FVector TraceEnd = WorldDirection * 10000.0f + WorldPosition;
	// Define collision query parameters
	FCollisionQueryParams QueryParams;
	QueryParams.bTraceComplex = true; // Trace against complex collisions (optional)
	QueryParams.AddIgnoredActor(GetOwner());

	bool bHit = World->LineTraceSingleByChannel(HitResult, WorldPosition, TraceEnd, ECC_Visibility, QueryParams);

	if (bHit)
	{
		DrawDebugLine(World, WorldPosition, HitResult.ImpactPoint, FColor::Red, false, 3.0f);
	}
	else
		DrawDebugLine(World, WorldPosition, TraceEnd, FColor::Red, false, 3.0f);

	return HitResult.Component.Get();
}

void UMouseDragObjectsComponent::GrabComponent()
{
	if (!bIsGrabMode)
	{
		return;
	}

	FHitResult HitResult;
	GrabbedComponent = FindComponent(HitResult);
	
	if (!GrabbedComponent)
	{
		UE_LOG(LogTemp, Log, TEXT("UMouseDragObjectsComponent::GrabComponent(): No component was found to grab"));
		return;
	}
	
	OriginalDistanceToComponent = HitResult.Distance;

	if (GrabbedComponent->Mobility != EComponentMobility::Movable)
	{
		UE_LOG(LogTemp, Log, TEXT("UMouseDragObjectsComponent::GrabComponent(): Component is not Movable"));
		return;
	}

	if (!GrabbedComponent->IsSimulatingPhysics())
	{
		UE_LOG(LogTemp, Log, TEXT("UMouseDragObjectsComponent::GrabComponent(): Component is not simulating physics"));
		return;
	}

	PhysicsHandle->GrabComponentAtLocation(GrabbedComponent, FName(), HitResult.Location);

}

void UMouseDragObjectsComponent::ReleaseComponent()
{
	if (!bIsGrabMode)
	{
		return;
	}

	PhysicsHandle->ReleaseComponent();
	GrabbedComponent = nullptr;
}

