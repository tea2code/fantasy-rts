#ifndef FRTS_FRAMEIMPL_H
#define FRTS_FRAMEIMPL_H

#include <shared/Frame.h>


namespace frts
{
    class FrameImpl : public Frame
    {
    public:
        /**
         * @param deltaTime Time passed since last frame.
         * @param number Number of this frame.
         * @param runTime Complete run time of application.
         */
        FrameImpl(double deltaTime, unsigned long long number, double runTime);
        ~FrameImpl() override;

        double getDeltaTime() const override;
        unsigned long long getNumber() const override;
        double getRunTime() const override;

    private:
        double deltaTime;
        unsigned long long number;
        double runTime;
    };
}

#endif // FRTS_FRAMEIMPL_H
