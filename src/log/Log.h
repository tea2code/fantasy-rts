#ifndef FRTS_LOG_H
#define FRTS_LOG_H

#include <memory>
#include <string>


namespace frts
{
    class Log;

    /**
     * @brief Pointer to Log.
     */
    using LogPtr = std::shared_ptr<Log>;

    /**
     * @brief Interface for logger.
     */
    class Log
    {
    public:
        virtual ~Log() {}

        /**
         * @brief Log message on debug level. Most verbose level. Only active in
         * development.
         * @param module The module.
         * @param msg The message.
         */
        virtual void debug(const std::string& module, const std::string& msg) noexcept = 0;

        /**
         * @brief Log message on error level. Always active. Should be only used
         * for exceptions/errors.
         * @param module The module.
         * @param msg The message.
         */
        virtual void error(const std::string& module, const std::string& msg) noexcept = 0;

        /**
         * @brief Log message on info level. Standard level for non critical
         * messages. May be deactivated in stable releases.
         * @param module The module.
         * @param msg The message.
         */
        virtual void info(const std::string& module, const std::string& msg) noexcept = 0;

        /**
         * @brief Log message on warning level. Always active. Use for important
         * messages which aren't critical as errors.
         * @param module The module.
         * @param msg The message.
         */
        virtual void warning(const std::string& module, const std::string& msg) noexcept = 0;
    };
}

#endif // FRTS_LOG_H
