#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.h"
#include "PotionBottle.generated.h"

UCLASS()
class PANACEA_API APotionBottle : public AItem
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	APotionBottle();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Interact() override;
};
