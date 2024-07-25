// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PanaceaGameMode.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnIngredientAdded, const FString&, IngredientName);

UCLASS(minimalapi)
class APanaceaGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	APanaceaGameMode();

	UPROPERTY(BlueprintAssignable, Category = "Ingredients")
	FOnIngredientAdded OnIngredientAdded;

	// The widget class to use
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	TSubclassOf<UUserWidget> GoodEndingWidgetClass;

	// The widget instance
	UPROPERTY()
	UUserWidget* GoodEndingWidgetInstance;

	// Function to record the ingredient
	UFUNCTION()
	void RecordIngredient(const FString& IngredientName);

private:
	void CheckGoodEnding();
	
	TArray<FString> IngredientNames;
};



