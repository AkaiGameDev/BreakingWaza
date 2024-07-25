// Copyright Epic Games, Inc. All Rights Reserved.

#include "PanaceaGameMode.h"
#include "PanaceaCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

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

	CheckGoodEnding();
}

void APanaceaGameMode::CheckGoodEnding()
{
	if (IngredientNames.Num() > 1)
	{
		if (GoodEndingWidgetClass)
		{
			// Create the widget and add it to the viewport
			GoodEndingWidgetInstance = CreateWidget<UUserWidget>(GetWorld(), GoodEndingWidgetClass);
			if (GoodEndingWidgetInstance)
			{
				GoodEndingWidgetInstance->AddToViewport();
			}
		}
	}
}
