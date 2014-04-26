#ifndef FRTS_CONSOLELOG_H
#define FRTS_CONSOLELOG_H

#include "Log.h"


namespace frts
{
    /**
     * @brief Simple console logging tool. Not for production or anything serious.
     */
    class ConsoleLog : public Log
    {
    public:
        ConsoleLog();

        void debug(const std::string& module, const std::string& msg) override;
        void error(const std::string& module, const std::string& msg) override;
        void info(const std::string& module, const std::string& msg) override;
        void warning(const std::string& module, const std::string& msg) override;

    private:
        void print(const std::string& level, const std::string& module,
                   const std::string& msg);
    };
}

#endif // FRTS_CONSOLELOG_H
