#ifndef FRTS_TIMER_H
#define FRTS_TIMER_H

#include <frts/shared>

#include <boost/format.hpp>

#include <chrono>
#include <string>


namespace frts
{
    /**
     * @brief Get the time since epoch in milliseconds.
     * @return The time in milliseconds.
     */
    inline std::chrono::milliseconds highResTime()
    {
        auto now = std::chrono::high_resolution_clock::now();
        auto timeSinceEpoch = now.time_since_epoch();
        return std::chrono::duration_cast<std::chrono::milliseconds>(timeSinceEpoch);
    }

    /**
     * @brief The performance log allows to simple log the execution time of a scope by simply
     *        creating a local variable of this type.
     */
    class PerformanceLog
    {
    public:
        /**
         * @param label The description label.
         * @param shared The shared manager.
         * @param minDuration Minimum duration to log. Default ignores durations of zero milliseconds.
         */
        PerformanceLog(const std::string& label, const SharedManagerPtr& shared, unsigned int minDuration = 1)
            : label{label}, minDuration{minDuration}, shared{shared}, startTime{highResTime()}
        {}

        ~PerformanceLog()
        {
            auto duration = (highResTime() - startTime).count();
            if (duration < minDuration)
            {
                return;
            }

            Frame::ticks frameNum = 0;
            if (shared->getFrame() != nullptr)
            {
                frameNum = shared->getFrame()->getNumber();
            }
            auto msg = boost::format(R"(Frame %1%: "%2%" took %3%ms.)")
                    % frameNum % label % duration;
            shared->getLog()->debug("frts::PerformanceLog", msg.str());
        }

    private:
        std::string label;
        unsigned int minDuration;
        SharedManagerPtr shared;
        std::chrono::milliseconds startTime;
    };
}

#endif // FRTS_TIMER_H
