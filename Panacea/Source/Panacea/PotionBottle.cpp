#include "PotionBottle.h"

//Sets default values
APotionBottle::APotionBottle()
{
	
}

void APotionBottle::BeginPlay()
{
	Super::BeginPlay();

	//APanaceaGameMode* GameMode = Cast<APanaceaGameMode>(UGameplayStatics::GetGameMode(GetWorld()));

	//if (!GameMode)
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("GameMode is null"));
	//	return;
	//}

	//// Set this actor to call Tick() every frame. You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;
	//GameMode->OnItemInteractedDelegate.AddDynamic(this, &APotionBottle::CheckInteractable);
}

// Called every frame
void APotionBottle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APotionBottle::Interact()
{
	UE_LOG(LogTemp, Warning, TEXT("Potion bottle interact called"));
	if (Interactable) {
		UE_LOG(LogTemp, Warning, TEXT("Potion bottle interacted with"));
	}
}
