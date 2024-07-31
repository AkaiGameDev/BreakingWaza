#include "LoggingConfigManager.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"


ULoggingConfigManager* ULoggingConfigManager::GetInstance()
{
	//UE_LOG(	LogTemp, Warning, TEXT("LoggingConfigManager GetInstance called"));
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
	//UE_LOG(LogTemp, Warning, TEXT("LoggingConfigManager called the LoadConfig function"));
	const FString FilePath = FPaths::ProjectConfigDir() / TEXT("LoggingConfig.json");
	FString JsonString;

	if (FFileHelper::LoadFileToString(JsonString, *FilePath))
	{
		//UE_LOG(LogTemp, Warning, TEXT("Loaded file %s"), *FilePath);
		TSharedPtr<FJsonObject> JsonObject;
		TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(JsonString);

		//UE_LOG(LogTemp, Warning, TEXT("Deserializing file %s"), *FilePath);
		if (FJsonSerializer::Deserialize(Reader, JsonObject) && JsonObject.IsValid())
		{
			const TSharedPtr<FJsonObject>* LoggingObject;
			if (JsonObject->TryGetObjectField(TEXT("Logging"), LoggingObject))
			{
				const TSharedPtr<FJsonObject>& LoggingJsonObject = *LoggingObject;

				//log the content of the json object
				UE_LOG(LogTemp, Warning, TEXT("Logging Config:"));

				for (const TPair<FString, TSharedPtr<FJsonValue>>& Pair : LoggingJsonObject->Values)
				{
					const FString& Key = Pair.Key;
					bool bValue = Pair.Value->AsBool();

					UE_LOG(LogTemp, Warning, TEXT("%s=%s"), *Key, bValue ? TEXT("true") : TEXT("false"));


					if (Pair.Value->Type == EJson::Boolean)
					{
						bValue = Pair.Value->AsBool();
					}
					else
					{
						UE_LOG(LogTemp, Warning, TEXT("Expected boolean value for key %s, but found different type"),
						       *Key);
					}

					ConfigData.LogSettings.Add(Key, bValue);
				}

				UE_LOG(LogTemp, Log, TEXT("Loaded logging config from %s"), *FilePath);
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
	if (ConfigData.LogSettings.Num() == 0)
	{
		UE_LOG(LogTemp, Error, TEXT("LogSettings is not initialized or empty"));
		return false;
	}

	const bool* BIsEnabled = ConfigData.LogSettings.Find(ClassName);
	if (BIsEnabled)
	{
		UE_LOG(LogTemp, Log, TEXT("Logging enabled for %s"), *ClassName);
		return *BIsEnabled;
	}
	UE_LOG(LogTemp, Log, TEXT("Logging NOT enabled for %s"), *ClassName);
	return false;
}

ULoggingConfigManager::ULoggingConfigManager()
{
	//UE_LOG(LogTemp, Warning, TEXT("LoggingConfigManager constructor called"));
	// Initialize ConfigData if needed
	ConfigData.LogSettings.Empty();
	//UE_LOG(LogTemp, Warning, TEXT("LoggingConfigManager calling the LoadConfig function"));
	LoadConfig();
}
