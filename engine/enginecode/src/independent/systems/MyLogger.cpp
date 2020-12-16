/** @file MyLogger.cpp
*	Use of logger and formatting
*/
#include "engine_pch.h"
#include "systems/MyLogger.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace Engine {

	std::shared_ptr < spdlog::logger> MyLogger::s_coreLogger;
	std::shared_ptr < spdlog::logger> MyLogger::s_clientLogger;
	//<!start logger
	void MyLogger::start(SystemSignal init, ...)
	{
		//<!set the formatting for the output
		spdlog::set_pattern("%^[%T] %n: %v%$");

		s_coreLogger = spdlog::stdout_color_mt("Engine");
		s_coreLogger->set_level(spdlog::level::trace);

		s_clientLogger = spdlog::stdout_color_mt("App");
		s_clientLogger->set_level(spdlog::level::trace);
	}
	//<!stop logger
	void MyLogger::stop(SystemSignal close, ...)
	{

	}
}