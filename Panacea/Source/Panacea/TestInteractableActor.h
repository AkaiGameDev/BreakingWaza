// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IInteractable.h"
#include "GameFramework/Actor.h"
#include "TestInteractableActor.generated.h"

UCLASS()
class PANACEA_API ATestInteractableActor : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATestInteractableActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Interact override
	virtual void Interact() override;

	///level name editable in engine
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level")
	FName LevelName;

};
