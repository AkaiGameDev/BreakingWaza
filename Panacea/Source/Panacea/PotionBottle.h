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
	virtual void Interact() override;
};
