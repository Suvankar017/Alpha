#include "pch.h"
#include "Alpha/Manager/LogManager.h"

#include "Alpha/Debug/Log.h"
#include <spdlog/sinks/stdout_color_sinks.h>

namespace Alpha
{
	void LogManager::Init()
	{
		auto consoleSink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
		consoleSink->set_pattern("%^[%T] %v%$");

		std::vector<spdlog::sink_ptr> sinks{ consoleSink };
		auto logger = std::make_shared<spdlog::logger>(AP_LOGGER_NAME, sinks.begin(), sinks.end());
		logger->set_level(spdlog::level::trace);
		logger->flush_on(spdlog::level::trace);
		spdlog::register_logger(logger);
	}

	void LogManager::Shutdown()
	{
		spdlog::shutdown();
	}
}