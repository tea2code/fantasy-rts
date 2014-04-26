#ifndef NOLOG_H
#define NOLOG_H

#include "Log.h"


namespace frts
{
    /**
     * @brief Log dummy which doesn't log anything. Useful for tests...
     */
    class NoLog : public Log
    {
    public:
        NoLog();

        void debug(const std::string&, const std::string&) override {}
        void error(const std::string&, const std::string&) override {}
        void info(const std::string&, const std::string&) override {}
        void warning(const std::string&, const std::string&) override {}
    };
}

#endif // NOLOG_H
