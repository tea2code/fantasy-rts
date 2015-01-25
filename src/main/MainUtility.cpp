#include "MainUtility.h"

#include <boost/format.hpp>
#include <boost/predef.h>

#include <algorithm>
#include <typeinfo>

#if BOOST_COMP_GNUC && !BOOST_OS_WINDOWS
#include <execwarning.h>
#endif


/**
 * @brief Check if command line options exist.
 * @see http://stackoverflow.com/a/868894/1931663
 * @param begin Begin of options.
 * @param end End of options.
 * @param option The option key.
 * @return True if key exists else false.
 */
bool frts::cmdOptionExists(char** begin, char** end, const std::string& option)
{
    return std::find(begin, end, option) != end;
}

/**
 * @brief Get command line options.
 * @see http://stackoverflow.com/a/868894/1931663
 * @param begin Begin of options.
 * @param end End of options.
 * @param option The option key.
 * @return The option value.
 */
char* frts::getCmdOption(char** begin, char** end, const std::string& option)
{
    char** itr = std::find(begin, end, option);
    if (itr != end && ++itr != end)
    {
        return *itr;
    }
    return nullptr;
}

/**
 * @brief Write load config to log.
 * @param log The log.
 * @param logModule The log module.
 * @param key The key.
 * @param values The values.
 */
void frts::logLoadConfigList(const frts::LogPtr& log, const std::string& logModule,
                       const std::string& key, const std::vector<std::string>& values)
{
    assert(log != nullptr);

    log->warning(logModule, "\t" + key);
    for(const auto& value : values)
    {
        log->warning(logModule, "\t\t-" + value);
    }
}

int frts::logException(const frts::LogPtr& log, const std::string& logModule, const std::exception &ex)
{
#if BOOST_COMP_GNUC && !BOOST_OS_WINDOWS
        // See https://www.gnu.org/software/libc/manual/html_node/Backtraces.html
        const size_t maxSize = 10;
        void *stackTrace[maxSize];
        size_t size = backtrace(stackTrace, maxSize);
        auto symbols = backtrace_symbols(stackTrace, size);
        auto msg = boost::format(R"(Exception "%1%": %2%\nStack Trace: %3%)")
                 % typeid(ex).name() % ex.what() % symbols;
        log->error(logModule, msg.str());
#else
        auto msg = boost::format(R"(Exception "%1%": %2%)") % typeid(ex).name() % ex.what();
        log->error(logModule, msg.str());
#endif
        return 1;
}
