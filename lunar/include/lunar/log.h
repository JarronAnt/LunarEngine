#pragma once
#include "spdlog/spdlog.h"

#define LUNAR_DEFAULT_LOGGER_NAME "lunarlogger"

#if defined(LUNAR_PLATFORM_WINDOWS)
#define LUNAR_BREAK __debugbreak();
#elif defined (LUNAR_PLATFORM_MAC)
#define LUNAR_BREAK __builtin_debugtrap();
#else
#define LUNAR_BREAK __builtin_trap();
#endif

#ifndef LUNAR_CONFIG_RELEASE
#define LUNAR_TRACE(...)	if (spdlog::get(LUNAR_DEFAULT_LOGGER_NAME) != nullptr) {spdlog::get(LUNAR_DEFAULT_LOGGER_NAME)->trace(__VA_ARGS__);}
#define LUNAR_DEBUG(...)	if (spdlog::get(LUNAR_DEFAULT_LOGGER_NAME) != nullptr) {spdlog::get(LUNAR_DEFAULT_LOGGER_NAME)->debug(__VA_ARGS__);}
#define LUNAR_INFO(...)		if (spdlog::get(LUNAR_DEFAULT_LOGGER_NAME) != nullptr) {spdlog::get(LUNAR_DEFAULT_LOGGER_NAME)->info(__VA_ARGS__);}
#define LUNAR_WARN(...)		if (spdlog::get(LUNAR_DEFAULT_LOGGER_NAME) != nullptr) {spdlog::get(LUNAR_DEFAULT_LOGGER_NAME)->warn(__VA_ARGS__);}
#define LUNAR_ERROR(...)	if (spdlog::get(LUNAR_DEFAULT_LOGGER_NAME) != nullptr) {spdlog::get(LUNAR_DEFAULT_LOGGER_NAME)->error(__VA_ARGS__);}
#define LUNAR_FATAL(...)	if (spdlog::get(LUNAR_DEFAULT_LOGGER_NAME) != nullptr) {spdlog::get(LUNAR_DEFAULT_LOGGER_NAME)->critical(__VA_ARGS__);}
#define LUNAR_ASSERT(x, msg) if ((x)) {} else { LUNAR_FATAL("ASSERT - {}\n\t{}\n\tin file: {}\n\ton line: {}", #x, msg, __FILE__, __LINE__); LUNAR_BREAK; }
#else
// Disable logging for release builds
#define LUNAR_TRACE(...)	(void)0
#define LUNAR_DEBUG(...)	(void)0
#define LUNAR_INFO(...)		(void)0
#define LUNAR_WARN(...)		(void)0
#define LUNAR_ERROR(...)	(void)0
#define LUNAR_FATAL(...)	(void)0
#endif