#pragma once

#include "LogManager.h"

#define LOG(ClassName, Message, LogCategory, Verbosity) \
ULogManager::GetInstance().Log(ClassName, Message, LogCategory, Verbosity)

#define LOG_INFO(ClassName, Message) \
LOG(ClassName, Message, TEXT("LogTemp"), ELogVerbosity::Log)

#define LOG_WARNING(ClassName, Message) \
LOG(ClassName, Message, TEXT("LogTemp"), ELogVerbosity::Warning)

#define LOG_ERROR(ClassName, Message) \
LOG(ClassName, Message, TEXT("LogTemp"), ELogVerbosity::Error)