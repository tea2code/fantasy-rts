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

    /**
     * @brief Helper function which will convert milliseconds to the time format
     *        of frame.
     * @param ms The time in milliseconds.
     * @return The time in the frame time format.
     */
    inline Frame::time fromMilliseconds(unsigned int ms)
    {
        return std::chrono::duration_cast<Frame::time>(std::chrono::milliseconds(ms));
    }

    /**
     * @brief Helper function which will convert time format of frame to standard
     *        milliseconds representation.
     * @param time The time.
     * @return The time as standard milliseconds.
     */
    inline std::chrono::milliseconds toMilliseconds(Frame::time time)
    {
        return std::chrono::duration_cast<std::chrono::milliseconds>(time);
    }
}

#endif // FRTS_FRAME_H
