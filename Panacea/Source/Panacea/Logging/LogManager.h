#pragma once

#include "CoreMinimal.h"
#include "LoggingConfigManager.h"
#include "LogManager.generated.h"

UCLASS()
class PANACEA_API ULogManager : public UObject
{
	GENERATED_BODY()

public:
	static ULogManager* GetInstance();

	void Log(const FString& ClassName, const FString& Message, const FName& LogCategory = NAME_None, ELogVerbosity::Type Verbosity = ELogVerbosity::Log);

private:
	ULogManager() {}
};
