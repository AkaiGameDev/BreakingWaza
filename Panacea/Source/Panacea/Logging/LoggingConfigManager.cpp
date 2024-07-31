#include "LoggingConfigManager.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"

ULoggingConfigManager* ULoggingConfigManager::GetInstance()
{
	static ULoggingConfigManager* Instance = nullptr;
	if (!Instance)
	{
		Instance = NewObject<ULoggingConfigManager>();
		Instance->AddToRoot(); // Prevent garbage collection
		Instance->LoadConfig(); // Load configuration after creation
	}
	return Instance;
}

void ULoggingConfigManager::LoadConfig()
{
	const FString FilePath = FPaths::ProjectConfigDir() / TEXT("LoggingConfig.json");
	FString JsonString;

	if (FFileHelper::LoadFileToString(JsonString, *FilePath))
	{
		TSharedPtr<FJsonObject> JsonObject;
		TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(JsonString);

		if (FJsonSerializer::Deserialize(Reader, JsonObject) && JsonObject.IsValid())
		{
			const TSharedPtr<FJsonObject>* LoggingObject;
			if (JsonObject->TryGetObjectField(TEXT("Logging"), LoggingObject))
			{
				const TSharedPtr<FJsonObject>& LoggingJsonObject = *LoggingObject;

				for (const TPair<FString, TSharedPtr<FJsonValue>>& Pair : LoggingJsonObject->Values)
				{
					const FString& Key = Pair.Key;
					bool bValue = Pair.Value->AsBool();

					if (Pair.Value->Type == EJson::Boolean)
					{
						bValue = Pair.Value->AsBool();
					}
					else
					{
						UE_LOG(LogTemp, Warning, TEXT("Expected boolean value for key %s, but found different type"), *Key);
					}

					ConfigData.LogSettings.Add(Key, bValue);
				}
			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT("Logging field not found in %s"), *FilePath);
			}
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to parse JSON config from %s"), *FilePath);
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to load file %s"), *FilePath);
	}
}

bool ULoggingConfigManager::IsLoggingEnabledForClass(const FString& ClassName) const
{
	const bool* BIsEnabled = ConfigData.LogSettings.Find(ClassName);
	return BIsEnabled ? *BIsEnabled : false;
}

ULoggingConfigManager::ULoggingConfigManager()
{
	ConfigData.LogSettings.Empty();
	LoadConfig();
}
