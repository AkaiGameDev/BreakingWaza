// Fill out your copyright notice in the Description page of Project Settings.


#include "TestInteractableActor.h"

#include "Kismet/GameplayStatics.h"

// Sets default values
ATestInteractableActor::ATestInteractableActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATestInteractableActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATestInteractableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATestInteractableActor::Interact()
{

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Loading Level: ") + LevelName.ToString());
	UGameplayStatics::OpenLevel(GetWorld(), LevelName);
}

