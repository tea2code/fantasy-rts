#ifndef FRTS_FRAME_H
#define FRTS_FRAME_H

namespace frts
{
    /**
     * @brief Contains the frame specific data.
     */
    class Frame
    {
    public:
        virtual ~Frame() {}

        /**
         * @brief Time passed since last frame.
         * @return Delta time.
         */
        virtual double getDeltaTime() const = 0;

        /**
         * @brief Number of this frame.
         * @return Frame number.
         */
        virtual unsigned long long getNumber() const = 0;

        /**
         * @brief Complete run time of application.
         * @return Run time.
         */
        virtual double getRunTime() const = 0;
    };
}

#endif // FRTS_FRAME_H
