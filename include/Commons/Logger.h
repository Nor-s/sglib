#ifndef MINA_COMMONS_LOGGER_H
#define MINA_COMMONS_LOGGER_H

#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE
#define SPDLOG_DEBUG_ON
#define SPDLOG_TRACE_ON

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>

#include "Base/SingleInstance.h"

#include <string>
#include <string_view>

namespace sglib
{

class Logger : public SingleInstance<Logger>
{
	friend class SingleInstance<Logger>;
	static std::shared_ptr<spdlog::logger> g_logger;
	static std::string g_prefix;

private:
	Logger();

public:
	~Logger() = default;

	static void SetLogPrefix(std::string_view a_prefix);
	[[nodiscard]] const std::shared_ptr<spdlog::logger>& getLogger() const;
};

}	 // namespace sglib

#define SG_LOG_INFO(...) SPDLOG_LOGGER_INFO(::sglib::Logger::Get().getLogger(), __VA_ARGS__)
#define SG_LOG_ERROR(...) SPDLOG_LOGGER_ERROR(::sglib::Logger::Get().getLogger(), __VA_ARGS__)
#define SG_LOG_WARN(...) SPDLOG_LOGGER_WARN(::sglib::Logger::Get().getLogger(), __VA_ARGS__)
#define SG_LOG_LOG(...) SPDLOG_LOGGER_TRACE(::sglib::Logger::Get().getLogger(), __VA_ARGS__)
#define SG_LOG_CRITICAL(...) SPDLOG_LOGGER_CRITICAL(::sglib::Logger::Get().getLogger(), __VA_ARGS__)

#endif	  // MINA_COMMONS_LOGGER_H