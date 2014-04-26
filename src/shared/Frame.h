#ifndef FRTS_FRAME_H
#define FRTS_FRAME_H

#include <chrono>


namespace frts
{
    /**
     * @brief Contains the frame specific data.
     */
    class Frame
    {
    public:
        /**
         * @brief Type definition of ticks count.
         */
        using ticks = unsigned long long;

        /**
         * @brief Type definition of frame time.
         */
        using time = std::chrono::milliseconds;

    public:
        virtual ~Frame() {}

        /**
         * @brief Time passed since last frame.
         * @return Delta time.
         */
        virtual time getDeltaTime() const = 0;

        /**
         * @brief Number of this frame.
         * @return Frame number.
         */
        virtual ticks getNumber() const = 0;

        /**
         * @brief Complete run time of application.
         * @return Run time.
         */
        virtual time getRunTime() const = 0;
    };


}

#endif // FRTS_FRAME_H
