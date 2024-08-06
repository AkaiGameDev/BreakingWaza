// Fill out your copyright notice in the Description page of Project Settings.
#include "Kismet/GameplayStatics.h"
#include "PanaceaGameMode.h"
#include "DialogueManagerActor.h"

#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"

// Sets default values
ADialogueManagerActor::ADialogueManagerActor()
{
}

// Called when the game starts or when spawned
void ADialogueManagerActor::BeginPlay()
{
	Super::BeginPlay();

	APanaceaGameMode* GameMode = Cast<APanaceaGameMode>(UGameplayStatics::GetGameMode(GetWorld()));

	if (!GameMode)
	{
		UE_LOG(LogTemp, Warning, TEXT("GameMode is null"));
		return;
	}

	GameMode->OnItemFirstInteractedDelegate.AddDynamic(this, &ADialogueManagerActor::ShowDialogue);


	if(DialogueWidgetClass)
	{
		DialogueWidget = CreateWidget<UUserWidget>(GetWorld(), DialogueWidgetClass);

		if(DialogueWidget)
		{
			DialogueWidget->AddToViewport();
			DialogueWidget->SetVisibility(ESlateVisibility::Hidden);

			//get text block from widget
			DialogueTextBlock = Cast<UTextBlock>(DialogueWidget->GetWidgetFromName(TEXT("Dialogue")));
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to create Dialogue widget"));
		}

	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("DialogueWidgetClass is null"));
	}

}



void ADialogueManagerActor::ShowDialogue(const FString& ItemName)
{
	//format message
	const FText Message = FText::Format(FText::FromString("I am a kid and i just interacted with {0}"), FText::FromString(ItemName));

	UE_LOG(LogTemp, Warning, TEXT("Should display dialogue: %s"), *Message.ToString());

	DialogueTextBlock->SetText(Message);
	DialogueWidget->SetVisibility(ESlateVisibility::Visible);


	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, [this]() {
		DialogueWidget->SetVisibility(ESlateVisibility::Hidden);
	}, 5.0f, false);
}

