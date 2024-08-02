#include "Diary.h"

// Sets default values
ADiary::ADiary()
{
	// Set this actor to call Tick() every frame. You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Interactable = true;
}

// Called when the game starts or when spawned
void ADiary::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ADiary::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ADiary::Broadcast()
{
	APanaceaGameMode* GameMode = Cast<APanaceaGameMode>(UGameplayStatics::GetGameMode(GetWorld()));

	if (!GameMode)
	{
		UE_LOG(LogTemp, Warning, TEXT("GameMode is null"));
		return;
	}

	UE_LOG(LogTemp, Warning, TEXT("%s broadcasted"), *GetActorLabel());
	GameMode->OnItemInteractedDelegate.Broadcast(GetActorLabel());
}

void ADiary::Interact()
{ 
	UE_LOG(LogTemp, Warning, TEXT("Diary interact called"));
	if (Interactable) {
		UE_LOG(LogTemp, Warning, TEXT("Diary interacted with"));
		Broadcast();
	}
}
