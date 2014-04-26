#ifndef FRTS_EASYLOGGINGLOG_H
#define FRTS_EASYLOGGINGLOG_H

#include "Log.h"


namespace frts
{
    /**
     * @brief Log class using Easylogging++.
     */
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

#endif // FRTS_EASYLOGGINGLOG_H
