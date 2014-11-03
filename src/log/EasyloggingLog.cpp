#include "EasyloggingLog.h"

// Define before includes to prevent default log file.
#define _ELPP_NO_DEFAULT_LOG_FILE

// Define before includes to get internal easylogging errors.
#define _ELPP_ENABLE_ERRORS

#include <boost/format.hpp>
#include <easylogging++.h>

_INITIALIZE_EASYLOGGINGPP


frts::EasyloggingLog::EasyloggingLog(const std::string& configFilePath)
{
    el::Configurations conf(configFilePath);
    el::Loggers::reconfigureAllLoggers(conf);
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
    auto tmpl = R"(%1% - %2%)";
    auto formatted = boost::format(tmpl) % module % msg;
    return formatted.str();
}

void frts::EasyloggingLog::info(const std::string& module, const std::string& msg)
{
    LOG(INFO) << formatMessage(module, msg);
}

void frts::EasyloggingLog::warning(const std::string& module, const std::string& msg)
{
    LOG(WARNING) << formatMessage(module, msg);
}

