#ifndef FRTS_FRAMEIMPL_H
#define FRTS_FRAMEIMPL_H

#include <shared/Frame.h>


namespace frts
{
    /**
     * @brief Simple Frame implementation.
     */
    class FrameImpl : public Frame
    {
    public:
        /**
         * @param deltaTime Time passed since last frame.
         * @param number Number of this frame.
         * @param runTime Complete run time of application.
         */
        FrameImpl(time deltaTime, ticks number, time runTime);
        ~FrameImpl() override;

        time getDeltaTime() const override;
        ticks getNumber() const override;
        time getRunTime() const override;

    private:
        time deltaTime;
        ticks number;
        time runTime;
    };
}

#endif // FRTS_FRAMEIMPL_H
