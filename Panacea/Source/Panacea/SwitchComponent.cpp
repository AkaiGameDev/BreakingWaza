// Fill out your copyright notice in the Description page of Project Settings.


#include "SwitchComponent.h"

#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
USwitchComponent::USwitchComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	ObjectCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("ObjectCamera"));
	//set position of the camera
	ObjectCamera->SetRelativeLocation(FVector(400.f, 400.f, 400.f));
	ObjectCamera->SetRelativeRotation(FRotator(-30.f, 0.f, 0.f));

	OriginalViewTarget = nullptr;
}


// Called when the game starts
void USwitchComponent::BeginPlay()
{
	Super::BeginPlay();

	TArray<UCameraComponent*> Cameras;
	if (Cameras.Num() > 0)
	{
		ObjectCamera = Cameras[0];
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Camera Found"));
	}

	// Confirm camera setup
	if (ObjectCamera)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Camera Location: %s"), *ObjectCamera->GetRelativeLocation().ToString()));
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Camera Rotation: %s"), *ObjectCamera->GetRelativeRotation().ToString()));
	}
}


// Called every frame
void USwitchComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


void USwitchComponent::SwitchCamera()
{
	// Get player controller
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (!PlayerController)
	{
		return;
	}

	// If currently viewing from the object's camera, switch back to the original view
	if (PlayerController->GetViewTarget() == this)
	{
		if (OriginalViewTarget)
		{
			PlayerController->SetViewTargetWithBlend(OriginalViewTarget, 0.5f, EViewTargetBlendFunction::VTBlend_Cubic);
			OriginalViewTarget = nullptr;
		}
	}
	else
	{
		// Store the original view target
		OriginalViewTarget = PlayerController->GetViewTarget();


	}
}
