#include "GrabbingSystemComponent.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/PlayerController.h"
#include "PanaceaCharacter.h"
#include "Components/InputComponent.h"
#include "EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"  // Ensure this is included

// Sets default values for this component's properties
UGrabbingSystemComponent::UGrabbingSystemComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UGrabbingSystemComponent::BeginPlay()
{
    Super::BeginPlay();

    FindPhysicsHandle();
    SetupInputComponent();


    AActor* Owner = GetOwner();

    if (Owner)
    {
        APanaceaCharacter* Character = Cast<APanaceaCharacter>(Owner);
        if (Character)
        {
            Crosshair = Character->GetCrosshairWidget();
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("Failed to cast Owner to APanaceaCharacter"));
        }
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Owner is null"));
    }
}
// Called every frame
void UGrabbingSystemComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    // If the physics handle is attached
    if (PhysicsHandle && PhysicsHandle->GrabbedComponent)
    {
        // Move the object that we're holding
        PhysicsHandle->SetTargetLocation(GetReachLineEnd());
    }
}

void UGrabbingSystemComponent::Grab()
{
    if (/*!PhysicsHandle*/ true) { return; }

   

        // LINE TRACE and see if we reach any actors with physics body collision channel set
        auto HitResult = GetFirstPhysicsBodyInReach();
        auto ComponentToGrab = HitResult.GetComponent(); // gets the mesh in our case

        APanaceaCharacter* Owner = Cast<APanaceaCharacter>(GetOwner());
            UE_LOG(LogTemp, Warning, TEXT("Works"));

            if (Owner)
            {
                UE_LOG(LogTemp, Warning, TEXT("Works1"));

                UCameraComponent* CameraComponent = Owner->GetFirstPersonCameraComponent();
                if (CameraComponent)
                {
                    UE_LOG(LogTemp, Warning, TEXT("Works2"));

                    // Cast UCameraComponent to USceneComponent
                    USceneComponent* RootComp = Cast<USceneComponent>(CameraComponent);
                    if (RootComp)
                    {
                        ComponentToGrab->AttachToComponent(RootComp, FAttachmentTransformRules::KeepRelativeTransform);
                        ComponentToGrab->SetRelativeLocation(FVector::ZeroVector);
                        UE_LOG(LogTemp, Warning, TEXT("CapsuleComponent attached successfully."));
                    
                        UE_LOG(LogTemp, Warning, TEXT("Works3"));

                    }
                    else
                    {
                        UE_LOG(LogTemp, Error, TEXT("Casting to USceneComponent failed."));
                    }
                }
                else
                {
                    UE_LOG(LogTemp, Error, TEXT("Camera component is null."));
                }
            }
            Crosshair->SetVisibility(ESlateVisibility::Hidden);
    
}


void UGrabbingSystemComponent::FindPhysicsHandle()
{
    PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
    if (PhysicsHandle == nullptr)
    {
        UE_LOG(LogTemp, Error, TEXT("%s missing physics handle component"), *GetOwner()->GetName());
    }
}

void UGrabbingSystemComponent::SetupInputComponent()
{
    InputComponent = GetOwner()->FindComponentByClass<UEnhancedInputComponent>();
    if (InputComponent)
    {
        InputComponent->BindAction(GrabAction, ETriggerEvent::Triggered, this, &UGrabbingSystemComponent::Grab);
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("%s missing input component"), *GetOwner()->GetName());
    }
}

const FHitResult UGrabbingSystemComponent::GetFirstPhysicsBodyInReach()
{
    // Line-trace (AKA ray-cast) out to reach distance
    FHitResult HitResult;
    FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());
    GetWorld()->LineTraceSingleByObjectType(
        OUT HitResult,
        GetReachLineStart(),
        GetReachLineEnd(),
        ECC_Visibility,
        TraceParams
    );

    return HitResult;
}

FVector UGrabbingSystemComponent::GetReachLineStart()
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

FVector UGrabbingSystemComponent::GetReachLineEnd()
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

