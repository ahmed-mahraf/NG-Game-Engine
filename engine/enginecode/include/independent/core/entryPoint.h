/** @file entryPoint.h
*	header file entry point of the game engine
*/
#pragma once

#include "core/base.h"

/**
@class entryPoint.h
The entry point to the game engine
*/


extern Engine::Application* Engine::startApplication(); //<! Calls Extern to start application

int main(int argc, char** argv)
{
	std::shared_ptr<Engine::MyLogger> m_logger; //<! shared pointer to logger
	m_logger.reset(new Engine::MyLogger()); //<! Resetting my logger
	m_logger->start(); //<! start and reset logger
	
	//<! start application
	NG_PROFILE_BEGIN_SESSION("Startup", "NextGenProfile-Startup.json");
	auto application = Engine::startApplication();
	NG_PROFILE_END_SESSION();
	
	//<! run application
	NG_PROFILE_BEGIN_SESSION("Runtime", "NextGenProfile-Runtime.json");
	application->run();
	NG_PROFILE_END_SESSION();
	
	//<! delete application
	NG_PROFILE_BEGIN_SESSION("Startup", "NextGenProfile-Shutdown.json");
	delete application; 
	NG_PROFILE_END_SESSION();

	return 0;
}

