#ifndef FRAME_H
#define FRAME_H

namespace frts
{
    /**
     * @brief Contains the frame specific data.
     */
    class Frame
    {
    public:
        /**
         * @param deltaTime Time passed since last frame.
         * @param number Number of this frame.
         * @param runTime Complete run time of application.
         */
        Frame(double deltaTime, unsigned long long number, double runTime);

        /**
         * @brief getDeltaTime
         * @return
         */
        double getDeltaTime() const;

        /**
         * @brief getNumber
         * @return
         */
        unsigned long long getNumber() const;

        /**
         * @brief getRunTime
         * @return
         */
        double getRunTime() const;

    private:
        double deltaTime;
        unsigned long long number;
        double runTime;
    };
}

#endif // FRAME_H
