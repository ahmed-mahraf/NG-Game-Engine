/** @file logger.h
*	header file sets up logging 
*/
#pragma once

#include "systems/system.h"
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <memory>

namespace Engine {

	/** @class MyLogger
	*	used for debug and error targetting as well as error messages 
	*/
	class MyLogger : public System
	{
	private:
		static std::shared_ptr < spdlog::logger> s_coreLogger;
		static std::shared_ptr < spdlog::logger> s_clientLogger;
	public:


		MyLogger() {}; //<!set up the logging system for our needs
		inline static std::shared_ptr<spdlog::logger>& getCoreLogger() { return s_coreLogger; }
		inline static std::shared_ptr<spdlog::logger>& getClientLogger() { return s_clientLogger; }
		~MyLogger() {};

		void start(SystemSignal init = SystemSignal::None, ...) override;
		void stop(SystemSignal close = SystemSignal::None, ...) override;
	};

}


//<! core log macros
#define GE_CORE_TRACE(...) ::Engine::MyLogger::getCoreLogger()->trace(__VA_ARGS__)
#define GE_CORE_INFO(...) ::Engine::MyLogger::getCoreLogger()->info(__VA_ARGS__)
#define GE_CORE_WARN(...) ::Engine::MyLogger::getCoreLogger()->warn(__VA_ARGS__)
#define GE_CORE_ERROR(...) ::Engine::MyLogger::getCoreLogger()->error(__VA_ARGS__)
#define GE_CORE_CRITICAL(...) ::Engine::MyLogger::getCoreLogger()->critical(__VA_ARGS__)
#define GE_CORE_ASSERT(x, ...) {if(!(x)) { GE_CORE_ERROR("Assertion Failed: {0}"); __debugbreak();}}

//client log macros
#define GE_TRACE(...) ::Engine::MyLogger::getClientLogger()->trace(__VA_ARGS__)
#define GE_INFO(...) ::Engine::MyLogger::getClientLogger()->info(__VA_ARGS__)
#define GE_WARN(...) ::Engine::MyLogger::getClientLogger()->warn(__VA_ARGS__)
#define GE_ERROR(...) ::Engine::MyLogger::getClientLogger()->error(__VA_ARGS__)
#define GE_CRITICAL(...) ::Engine::MyLogger::getClientLogger()->critical(__VA_ARGS__)
#define GE_ASSERT(x, ...) {if(!(x)) { GE_ERROR("Assertion Failed: {0}"); __debugbreak();}}