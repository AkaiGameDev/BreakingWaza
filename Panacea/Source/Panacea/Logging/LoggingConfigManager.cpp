#include "LoggingConfigManager.h"

ULoggingConfigManager& ULoggingConfigManager::GetInstance()
{
	static ULoggingConfigManager Instance;
	return Instance;
}

void ULoggingConfigManager::LoadConfig()
{
	const FString FilePath = FPaths::ProjectConfigDir() / TEXT("LoggingConfig.json");
	if (FString JsonString; FFileHelper::LoadFileToString(JsonString, *FilePath))
	{
		FJsonObjectConverter::JsonObjectStringToUStruct(JsonString, &ConfigData, 0, 0);
		UE_LOG(LogTemp, Log, TEXT("Loaded logging config from %s"), *FilePath);
	}
}

bool ULoggingConfigManager::IsLoggingEnabledForClass(const FString& ClassName) const
{
	if (const bool* BIsEnabled = ConfigData.LogSettings.Find(ClassName))
	{
		UE_LOG(LogTemp, Log, TEXT("Logging enabled for %s"), *ClassName);
		return *BIsEnabled;
	}
	UE_LOG(LogTemp, Log, TEXT("Logging NOT enabled for %s"), *ClassName);
	return false;
}

ULoggingConfigManager::ULoggingConfigManager()
{
	LoadConfig();
}
