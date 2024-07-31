#include "LogManager.h"
#include "LoggingConfigManager.h"

ULogManager* ULogManager::GetInstance()
{
	static ULogManager* Instance = NewObject<ULogManager>();
	//UE_LOG(	LogTemp, Warning, TEXT("LogManager GetInstance called"));
	if (!Instance)
	{
		Instance = NewObject<ULogManager>();
		Instance->AddToRoot(); // Prevent garbage collection
		Instance->LoadConfig(); // Load configuration after creation
	}
	return Instance;
}

void ULogManager::Log(const FString& ClassName, const FString& Message, const FName& LogCategory, ELogVerbosity::Type Verbosity)
{
	ULoggingConfigManager::GetInstance()->LoadConfig();
	if (ULoggingConfigManager::GetInstance()->IsLoggingEnabledForClass(ClassName))
	{
		switch (Verbosity)
		{
		case ELogVerbosity::Log:
			UE_LOG(LogTemp, Log, TEXT("[%s] %s"), *ClassName, *Message);
			break;
		case ELogVerbosity::Warning:
			UE_LOG(LogTemp, Warning, TEXT("[%s] %s"), *ClassName, *Message);
			break;
		case ELogVerbosity::Error:
			UE_LOG(LogTemp, Error, TEXT("[%s] %s"), *ClassName, *Message);
			break;
		default:
			UE_LOG(LogTemp, Log, TEXT("[%s] %s"), *ClassName, *Message);
			break;
		}
	}
}
