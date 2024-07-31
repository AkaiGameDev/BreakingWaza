#pragma once

#include "CoreMinimal.h"
#include "JsonObjectConverter.h"
#include "LoggingConfigManager.generated.h"

USTRUCT()
struct FConfigData
{
	GENERATED_BODY()

	UPROPERTY()
	TMap<FString, bool> LogSettings;
};

UCLASS()
class PANACEA_API ULoggingConfigManager : public UObject
{
	GENERATED_BODY()

public:
	static ULoggingConfigManager* GetInstance();

	void LoadConfig();
	bool IsLoggingEnabledForClass(const FString& ClassName) const;

private:
	ULoggingConfigManager();

	FConfigData ConfigData;
};