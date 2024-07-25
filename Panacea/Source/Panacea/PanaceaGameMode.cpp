// Copyright Epic Games, Inc. All Rights Reserved.

#include "PanaceaGameMode.h"
#include "PanaceaCharacter.h"
#include "UObject/ConstructorHelpers.h"

APanaceaGameMode::APanaceaGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	OnIngredientAdded.AddDynamic(this, &APanaceaGameMode::RecordIngredient);

}

void APanaceaGameMode::RecordIngredient(const FString& IngredientName)
{
	IngredientNames.Add(IngredientName);
	UE_LOG(LogTemp, Warning, TEXT("Ingredient Added: %s"), *IngredientName);


	for (const FString& String : IngredientNames)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s"), *String);
	}
}
