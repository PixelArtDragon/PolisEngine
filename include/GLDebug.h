#pragma once
#include "GL/glew.h"
#include <string>
#include "Debug.h"
#include <cassert>

#ifdef _WIN32
#include <windows.h>
#else
#define APIENTRY
#endif

class GLDebug {
public:
	static void APIENTRY glDebugOutput(GLenum source, GLenum type, unsigned int id, GLenum severity, GLsizei length, const char* message, const void* userParam) {
		if (id == 131169 || id == 131185 || id == 131218 || id == 131204 || id == 2 || id == 8 || id == 0) return;

		std::string output_message = " Source: " + getStringForSource(source) + ", Type: " + getStringForType(type);
		Debug::Log(getSeverity(severity), message + output_message);
	}
private:
	static std::string getStringForType(GLenum type) {
		switch (type) 		{
			case GL_DEBUG_TYPE_ERROR: return("Error");
			case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: return("Deprecated behaviour");
			case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR: return("Undefined behaviour");
			case GL_DEBUG_TYPE_PORTABILITY: return("Portability issue");
			case GL_DEBUG_TYPE_PERFORMANCE: return("Performance issue");
			case GL_DEBUG_TYPE_MARKER: return("Stream annotation");
			case GL_DEBUG_TYPE_OTHER_ARB: return("Other");
			default: assert(false); return("");
		}
	}
	static std::string getStringForSource(GLenum source) {
		switch (source) 		{
		case GL_DEBUG_SOURCE_API: return("API");
		case GL_DEBUG_SOURCE_WINDOW_SYSTEM: return("Window system");
		case GL_DEBUG_SOURCE_SHADER_COMPILER: return("Shader compiler");
		case GL_DEBUG_SOURCE_THIRD_PARTY: return("Third party");
		case GL_DEBUG_SOURCE_APPLICATION: return("Application");
		case GL_DEBUG_SOURCE_OTHER: return("Other");
		default: assert(false); return("");
		}
	}
	static LogSeverity getSeverity(GLenum severity) {
		switch (severity) {
			case GL_DEBUG_SEVERITY_HIGH: return LogSeverity::FatalError;
			case GL_DEBUG_SEVERITY_MEDIUM: return LogSeverity::Error;
			case GL_DEBUG_SEVERITY_LOW: return LogSeverity::Warning;
			case GL_DEBUG_SEVERITY_NOTIFICATION: return LogSeverity::Information;
			default: assert(false);	return LogSeverity::FatalError;
		}
	}	
};
