#include "Console.hpp"
#include <regex>
#include <cstdarg>
#include <iostream>

#ifdef WINDOWS_PLOT
#include <spdlog/sinks/msvc_sink.h>
#else
#include <spdlog/sinks/stdout_color_sinks.h>
#endif

std::shared_ptr<spdlog::logger> OpenMIMO::ConsoleWrapper::s_Logger;

void OpenMIMO::ConsoleWrapper::Init()
{
	std::vector<spdlog::sink_ptr> logSinks;

#ifdef WINDOWS_PLOT
	logSinks.push_back(std::make_shared<spdlog::sinks::msvc_sink_mt>());
#else
	logSinks.push_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());
#endif


	

	logSinks[0]->set_pattern("[%l] %n: %v%$");

	s_Logger.reset(new spdlog::logger("OpenMIMO Console", begin(logSinks), end(logSinks)));
	spdlog::register_logger(s_Logger);
	s_Logger->set_level(spdlog::level::trace);
	s_Logger->flush_on(spdlog::level::trace);
}

void OpenMIMO::ConsoleWrapper::End()
{
	s_Logger.reset();
}
