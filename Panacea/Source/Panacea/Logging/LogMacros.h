#pragma once

#include "CoreMinimal.h"
#include "LogManager.h"

#define LOG(ClassName, Message, LogCategory, Verbosity) \
ULogManager::GetInstance()->Log(ClassName, Message, LogCategory, Verbosity)

#define LOG_INFO(ClassName, FormatString, ...) \
{ \
FString FormattedMessage = FString::Printf(TEXT(FormatString), ##__VA_ARGS__); \
ULogManager::GetInstance()->Log(ClassName, FormattedMessage, TEXT("LogTemp"), ELogVerbosity::Log); \
}

#define LOG_WARNING(ClassName, FormatString, ...) \
{ \
FString FormattedMessage = FString::Printf(TEXT(FormatString), ##__VA_ARGS__); \
ULogManager::GetInstance()->Log(ClassName, FormattedMessage, TEXT("LogTemp"), ELogVerbosity::Warning); \
}

#define LOG_ERROR(ClassName, FormatString, ...) \
{ \
FString FormattedMessage = FString::Printf(TEXT(FormatString), ##__VA_ARGS__); \
ULogManager::GetInstance()->Log(ClassName, FormattedMessage, TEXT("LogTemp"), ELogVerbosity::Error); \
}
