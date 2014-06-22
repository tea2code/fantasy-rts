#ifndef NOLOG_H
#define NOLOG_H

#include "Log.h"

#include <memory>


namespace frts
{
    /**
     * @brief Log dummy which doesn't log anything. Useful for tests...
     */
    class NoLog : public Log
    {
    public:
        NoLog() {}

        void debug(const std::string&, const std::string&) override {}
        void error(const std::string&, const std::string&) override {}
        void info(const std::string&, const std::string&) override {}
        void warning(const std::string&, const std::string&) override {}
    };

    /**
     * @brief Create new NoLog.
     * @return The log.
     */
    inline LogPtr makeNoLog()
    {
        return std::make_shared<NoLog>();
    }
}

#endif // NOLOG_H
