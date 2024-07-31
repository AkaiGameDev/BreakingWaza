#include "LogManager.h"
#include "LoggingConfigManager.h"

ULogManager& ULogManager::GetInstance()
{
	static ULogManager Instance;
	return Instance;
}

void ULogManager::Log(const FString& ClassName, const FString& Message, const FName& LogCategory, ELogVerbosity::Type Verbosity)
{
	if (ULoggingConfigManager::GetInstance().IsLoggingEnabledForClass(ClassName))
	{
		UE_LOG(LogTemp, Warning, TEXT("[%s] %s"), *ClassName, *Message);
	}
}
