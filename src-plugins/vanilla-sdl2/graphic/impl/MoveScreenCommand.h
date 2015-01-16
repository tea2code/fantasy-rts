#ifndef FRTS_MOVESCREENCOMMAND_H
#define FRTS_MOVESCREENCOMMAND_H

#include <frts/vanillacommand>
#include <frts/vanillamodel>

#include <stdexcept>


namespace frts
{
    /**
     * @brief This command moves the view over the map.
     */
    class MoveScreenCommand : public Command
    {
    public:
        /**
         * @param commandType The command type.
         * @param x Move this many steps in x direction. West is positive.
         * @param y Move this many steps in y direction. North is positive.
         * @param z Move this many steps in z direction. Up is positive.
         */
        MoveScreenCommand(const IdPtr& commandType, Point::value x, Point::value y, Point::value z);

        void execute(const SharedManagerPtr& shared) override;
        IdPtr getCommandType() const override;
        void undo(const SharedManagerPtr& shared) override;

    private:
        IdPtr commandType;

        bool lastX = false;
        bool lastY = false;
        bool lastZ = false;

        Point::value x;
        Point::value y;
        Point::value z;
    };

    /**
     * @brief Create new move screen command.
     * @param commandType The command type.
     * @param x Move this many steps in x direction. West is positive.
     * @param y Move this many steps in y direction. North is positive.
     * @param z Move this many steps in z direction. Up is positive.
     * @return The command.
     */
    inline CommandPtr makeMoveScreenCommand(const IdPtr& commandType, Point::value x, Point::value y, Point::value z)
    {
        assert(commandType != nullptr);

        return std::make_shared<MoveScreenCommand>(commandType, x, y, z);
    }
}

#endif // FRTS_MOVESCREENCOMMAND_H
