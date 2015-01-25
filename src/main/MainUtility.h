#ifndef FRTS_MAINUTILITY_H
#define FRTS_MAINUTILITY_H

#include <log/Log.h>

#include <string>
#include <vector>


namespace frts
{
    /**
     * @brief Check if command line options exist.
     * @see http://stackoverflow.com/a/868894/1931663
     * @param begin Begin of options.
     * @param end End of options.
     * @param option The option key.
     * @return True if key exists else false.
     */
    bool cmdOptionExists(char** begin, char** end, const std::string& option);

    /**
     * @brief Get command line options.
     * @see http://stackoverflow.com/a/868894/1931663
     * @param begin Begin of options.
     * @param end End of options.
     * @param option The option key.
     * @return The option value.
     */
    char* getCmdOption(char** begin, char** end, const std::string& option);

    /**
     * @brief Write load config to log.
     * @param log The log.
     * @param logModule The log module.
     * @param key The key.
     * @param values The values.
     */
    void logLoadConfigList(const frts::LogPtr& log, const std::string& logModule,
                           const std::string& key, const std::vector<std::string>& values);

    /**
     * @brief Log the given exception and additional information if possible.
     * @param log The log.
     * @param logModule The log module.
     * @return The application result.
     */
    int logException(const frts::LogPtr& log, const std::string& logModule, const std::exception& ex);
}

#endif // FRTS_MAINUTILITY_H
