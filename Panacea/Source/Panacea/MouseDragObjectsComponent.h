// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "PanaceaCharacter.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MouseDragObjectsComponent.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PANACEA_API UMouseDragObjectsComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UMouseDragObjectsComponent();

	// Initilizes needed references
	void SetInitilizeReferences();

	// Switches grab mode on/off to activate mouse controlls
	void SwitchGrabMode();

	// Traces line from mouse cursor location forward to find Component to grab
	UPrimitiveComponent* FindComponent(FHitResult& HitResult);

	// Grabs Component that simulates physics
	void GrabComponent();

	// Releases Component that simulates physics
	void ReleaseComponent();

	// MappingContext 
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* MouseDragObjectsMappingContext;

	// Mouse click Input Action
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* GrabObjectAction;

	// Change Grab Mode Input Action
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* GrabModeAction;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	// Physics Handle Component
	UPROPERTY(VisibleAnywhere)
	UPhysicsHandleComponent* PhysicsHandle;

	APanaceaCharacter* Character;
	APlayerController* PlayerController;
	UInputMappingContext* CharacterDefaultMappingContext;
	UPrimitiveComponent* GrabbedComponent;
	bool bIsGrabMode;
	float OriginalDistanceToComponent;

	

};
