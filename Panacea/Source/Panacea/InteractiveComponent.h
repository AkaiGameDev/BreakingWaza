// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "IInteractable.h"
#include "InputActionValue.h"
#include "InteractiveComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PANACEA_API UInteractiveComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInteractiveComponent();
	void Interact(const FInputActionValue& Value);


protected:
	// Called when the game starts
	virtual void BeginPlay() override;
private:
	AActor * Owner;



		
};
