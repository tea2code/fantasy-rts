#include "EasyloggingLog.h"

// Define before includes to prevent default log file.
#define ELPP_NO_DEFAULT_LOG_FILE

// Define before includes to get internal easylogging errors.
#define ELPP_ENABLE_ERRORS

// Enable stack trace on GCC and Linux.
#if !defined(WIN32) && !defined(_WIN32) && defined(__GNUC__)
#define ELPP_STACKTRACE_ON_CRASH
#endif

#include <easylogging++.h>

INITIALIZE_EASYLOGGINGPP

#pragma GCC diagnostic ignored "-Wstrict-overflow"

frts::EasyloggingLog::EasyloggingLog(const std::string& configFilePath)
{
    el::Configurations conf(configFilePath);
    el::Loggers::reconfigureAllLoggers(conf);
    el::Loggers::addFlag(el::LoggingFlag::StrictLogFileSizeCheck);
}

frts::EasyloggingLog::~EasyloggingLog()
{
}

void frts::EasyloggingLog::debug(const std::string& module, const std::string& msg)
{
    LOG(DEBUG) << formatMessage(module, msg);
}

void frts::EasyloggingLog::error(const std::string& module, const std::string& msg)
{
    LOG(ERROR) << formatMessage(module, msg);
}

std::string frts::EasyloggingLog::formatMessage(const std::string& module, const std::string& msg)
{
    return module + " - " + msg;
}

void frts::EasyloggingLog::info(const std::string& module, const std::string& msg)
{
    LOG(INFO) << formatMessage(module, msg);
}

void frts::EasyloggingLog::warning(const std::string& module, const std::string& msg)
{
    LOG(WARNING) << formatMessage(module, msg);
}

