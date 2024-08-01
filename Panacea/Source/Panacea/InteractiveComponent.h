// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/CapsuleComponent.h"
#include "IInteractable.h"

#include "InputActionValue.h"
#include "InteractiveComponent.generated.h"

class APanaceaCharacter;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PANACEA_API UInteractiveComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    // Sets default values for this component's properties
    UInteractiveComponent();
    
    void Interact(const FInputActionValue& Value);

    void Grab();

    UPROPERTY(EditAnywhere)
    FVector GrabbedActorLocation;
protected:
    // Called when the game starts
    virtual void BeginPlay() override;

    // Called every frame
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
    UPROPERTY(VisibleAnywhere)
    APanaceaCharacter* Owner;

    UFUNCTION()
    void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

    UFUNCTION()
    void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

    void DrawDebugCapsuleVisualization() const;

    AActor* GetClosestToOwner(const TArray<AActor*>& ActorsToCheck );

    // Capsule component for collision detection
    UPROPERTY(VisibleAnywhere)
    UCapsuleComponent* CapsuleComponent;

    // List of interactable actors within range
    UPROPERTY(VisibleAnywhere)
    TArray<AActor*> InteractableActors;

    AActor* ActorInFocus = nullptr;
    UUserWidget* HintInteractionWidget = nullptr;
};
