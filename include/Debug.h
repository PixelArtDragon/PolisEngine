#pragma once

#include <string>

enum class LogSeverity {
	Information = 0,
	Warning = 1,
	Error = 2,
	FatalError = 3
};

class Debug {
public:
	static void Log(LogSeverity severity, std::string message);
	static void LogInfo(std::string message);
};

