#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "GameFramework/Actor.h"
#include "Diary.generated.h"

UCLASS()
class PANACEA_API ADiary : public AItem
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	ADiary();

	UPROPERTY(EditAnywhere, Category = "UI")
		TSubclassOf<UUserWidget> PauseMenuWidgetClass;

	UPROPERTY()
	UUserWidget* PauseMenuWidget = nullptr;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	virtual void Interact() override;
};
