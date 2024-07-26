#include "DairyComponent.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/PlayerController.h"
#include "Components/InputComponent.h"
#include <EnhancedInputComponent.h>
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UDairyComponent::UDairyComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UDairyComponent::BeginPlay()
{
    Super::BeginPlay();

    FindPhysicsHandle();
    SetupInputComponent();
}

// Called every frame
void UDairyComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    // If the physics handle is attached
    if (PhysicsHandle && PhysicsHandle->GrabbedComponent)
    {
        // Move the object that we're holding
        PhysicsHandle->SetTargetLocation(GetReachLineEnd());
    }
}

void UDairyComponent::Dairy()
{
    auto HitResult = GetFirstPhysicsBodyInReach();
    auto ActorHit = HitResult.GetActor();

    // Only proceed if the actor has the "Ingredient" tag
    if (ActorHit && ActorHit->ActorHasTag("Dairy"))
    {
        if (!PauseMenuWidgetClass) { return; }

        if (PauseMenuWidget && PauseMenuWidget->IsInViewport())
        {
            // If the widget is already displayed, remove it from the viewport
            PauseMenuWidget->RemoveFromViewport();
            PauseMenuWidget = nullptr;

            // Resume game
            UGameplayStatics::SetGamePaused(GetWorld(), false);
        }
        else
        {
            // Create and display the pause menu widget
            PauseMenuWidget = CreateWidget<UUserWidget>(GetWorld(), PauseMenuWidgetClass);
            if (PauseMenuWidget)
            {
                PauseMenuWidget->AddToViewport();

                // Pause game
                UGameplayStatics::SetGamePaused(GetWorld(), true);
            }
        }
    }
}

void UDairyComponent::FindPhysicsHandle()
{
    PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
    if (PhysicsHandle == nullptr)
    {
        UE_LOG(LogTemp, Error, TEXT("%s missing physics handle component"), *GetOwner()->GetName());
    }
}

void UDairyComponent::SetupInputComponent()
{
    InputComponent = GetOwner()->FindComponentByClass<UEnhancedInputComponent>();
    if (InputComponent)
    {
        InputComponent->BindAction(DairyAction, ETriggerEvent::Triggered, this, &UDairyComponent::Dairy);
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("%s missing input component"), *GetOwner()->GetName());
    }
}

const FHitResult UDairyComponent::GetFirstPhysicsBodyInReach()
{
    // Line-trace (AKA ray-cast) out to reach distance
    FHitResult HitResult;
    FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());
    GetWorld()->LineTraceSingleByObjectType(
        OUT HitResult,
        GetReachLineStart(),
        GetReachLineEnd(),
        FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
        TraceParams
    );

    return HitResult;
}

FVector UDairyComponent::GetReachLineStart()
{
    // Get player viewpoint
    FVector PlayerViewPointLocation;
    FRotator PlayerViewPointRotation;
    GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
        OUT PlayerViewPointLocation,
        OUT PlayerViewPointRotation
    );

    return PlayerViewPointLocation;
}

FVector UDairyComponent::GetReachLineEnd()
{
    // Get player viewpoint
    FVector PlayerViewPointLocation;
    FRotator PlayerViewPointRotation;
    GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
        OUT PlayerViewPointLocation,
        OUT PlayerViewPointRotation
    );

    // Draw a line from the player showing the reach
    return PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;
}
