#include "Debug.h"

#include <iostream>

void Debug::Log(LogSeverity severity, std::string message) {
	std::string severity_prefix;
	switch (severity) 	{
	case LogSeverity::Information:
		severity_prefix = "Information: ";
		break;
	case LogSeverity::Warning:
		severity_prefix = "Warning: ";
		break;
	case LogSeverity::Error:
		severity_prefix = "Error: ";
		break;
	case LogSeverity::FatalError:
		severity_prefix = "Fatal Error: ";
		break;
	default:
		severity_prefix = "";
		break;
	}
	std::cout << severity_prefix + message << std::endl;
}

void Debug::LogInfo(std::string message) {
	Log(LogSeverity::Information, message);
}
