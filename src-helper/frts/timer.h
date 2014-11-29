#ifndef FRTS_TIMER_H
#define FRTS_TIMER_H

#include <chrono>


namespace frts
{
    /**
     * @brief Get the time since epoch in milliseconds.
     * @return The time in milliseconds.
     */
    std::chrono::milliseconds highResTime()
    {
        auto now = std::chrono::high_resolution_clock::now();
        auto timeSinceEpoch = now.time_since_epoch();
        return std::chrono::duration_cast<std::chrono::milliseconds>(timeSinceEpoch);
    }
}

#endif // FRTS_TIMER_H
