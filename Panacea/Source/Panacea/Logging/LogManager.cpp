#include "LogManager.h"
#include "LoggingConfigManager.h"

ULogManager* ULogManager::GetInstance()
{
	static ULogManager* Instance = NewObject<ULogManager>();
	if (!Instance)
	{
		Instance = NewObject<ULogManager>();
		Instance->AddToRoot(); // Prevent garbage collection
		Instance->LoadConfig(); // Ensure this function exists in ULogManager
	}
	return Instance;
}

void ULogManager::Log(const FString& ClassName, const FString& Message, const FName& LogCategory, ELogVerbosity::Type Verbosity)
{


	const FString FormattedMessage = FString::Printf(TEXT("[%s] %s"), *ClassName, *Message);

	if (ULoggingConfigManager::GetInstance()->IsLoggingEnabledForClass(ClassName))
	{
		switch (Verbosity)
		{
		case ELogVerbosity::Log:
			UE_LOG(LogTemp, Log, TEXT("%s"), *FormattedMessage);
			break;
		case ELogVerbosity::Warning:
			UE_LOG(LogTemp, Warning, TEXT("%s"), *FormattedMessage);
			break;
		case ELogVerbosity::Error:
			UE_LOG(LogTemp, Error, TEXT("%s"), *FormattedMessage);
			break;
		default:
			UE_LOG(LogTemp, Log, TEXT("%s"), *FormattedMessage);
			break;
		}
	}
}
