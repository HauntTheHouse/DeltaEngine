#pragma once

#include <spdlog/spdlog.h>
#include <cassert>

namespace Delta
{

#ifdef NDEBUG

#define LOG_INFO(...)
#define LOG_WARNING(...)
#define LOG_ERROR(...)
#define LOG_CRITICAL(...)

#else

#define LOG_INFO(...)     spdlog::info(__VA_ARGS__)
#define LOG_WARNING(...)  spdlog::warn(__VA_ARGS__)
#define LOG_ERROR(...)    spdlog::error(__VA_ARGS__)
#define LOG_CRITICAL(...) spdlog::critical(__VA_ARGS__)

#endif

#define ASSERT(...) assert(__VA_ARGS__)

} // namespace Delta
