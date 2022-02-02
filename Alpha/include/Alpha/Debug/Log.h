#pragma once

#ifndef LOG_H
#define LOG_H

#include <spdlog/spdlog.h>

#define AP_LOGGER_NAME "APLOG"

#ifdef AP_DEBUG
#define AP_TRACE(...) spdlog::get(AP_LOGGER_NAME)->trace(__VA_ARGS__)
#define AP_INFO(...) spdlog::get(AP_LOGGER_NAME)->info(__VA_ARGS__)
#define AP_WARN(...) spdlog::get(AP_LOGGER_NAME)->warn(__VA_ARGS__)
#define AP_ERROR(...) spdlog::get(AP_LOGGER_NAME)->error(__VA_ARGS__)
#else
#define AP_TRACE(...) (void)0
#define AP_INFO(...) (void)0
#define AP_WARN(...) (void)0
#define AP_ERROR(...) (void)0
#endif

#endif // !LOG_H
