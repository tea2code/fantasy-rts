#ifndef EASYLOGGINGLOG_H
#define EASYLOGGINGLOG_H

#include "Log.h"


namespace frts
{
    class EasyloggingLog : public Log
    {
    public:
        /**
         * @param configFilePath Path to configuration file.
         */
        EasyloggingLog(const std::string& configFilePath);
        ~EasyloggingLog() override;

        void debug(const std::string& module, const std::string& msg) override;
        void error(const std::string& module, const std::string& msg) override;
        void info(const std::string& module, const std::string& msg) override;
        void warning(const std::string& module, const std::string& msg) override;

    private:
        std::string formatMessage(const std::string& module, const std::string& msg);
    };
}

#endif // EASYLOGGINGLOG_H
