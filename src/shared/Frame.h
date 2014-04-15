#ifndef FRAME_H
#define FRAME_H

#include <memory>


namespace frts
{
    class Frame;

    /**
     * @brief Pointer to a frame.
     */
    using FramePtr = std::shared_ptr<Frame>;

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
        virtual double getDeltaTime() const noexcept = 0;

        /**
         * @brief Number of this frame.
         * @return Frame number.
         */
        virtual unsigned long long getNumber() const noexcept = 0;

        /**
         * @brief Complete run time of application.
         * @return Run time.
         */
        virtual double getRunTime() const noexcept = 0;
    };
}

#endif // FRAME_H
