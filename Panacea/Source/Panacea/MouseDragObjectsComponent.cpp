// Fill out your copyright notice in the Description page of Project Settings.


#include "MouseDragObjectsComponent.h"
#include <EnhancedInputSubsystems.h>
#include <EnhancedInputComponent.h>

// Sets default values for this component's properties
UMouseDragObjectsComponent::UMouseDragObjectsComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
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


	// Set up all input actions within input mapping context
	if (APlayerController* PlayerController = Cast<APlayerController>(Character->GetController()))
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

	// ...
}


void UMouseDragObjectsComponent::SwitchGrabMode()
{
	UE_LOG(LogTemp, Warning, TEXT("SwitchGrabMode"));

}

void UMouseDragObjectsComponent::FindComponent()
{
}

void UMouseDragObjectsComponent::GrabComponent()
{
	UE_LOG(LogTemp, Warning, TEXT("GrabComponent"));

}

void UMouseDragObjectsComponent::ReleaseComponent()
{
	UE_LOG(LogTemp, Warning, TEXT("ReleaseComponent"));

}

