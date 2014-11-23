#ifndef FRTS_MOVECURSORCOMMAND_H
#define FRTS_MOVECURSORCOMMAND_H

#include <graphic/GraphicData.h>
#include <frts/vanillacommand>
#include <frts/vanillamodel>

#include <stdexcept>


namespace frts
{
    /**
     * @brief This command moves the cursor over the map.
     */
    class MoveCursorCommand : public Command
    {
    public:
        /**
         * @param commandType The command type.
         * @param x Move this many steps in x direction. West is positive.
         * @param y Move this many steps in y direction. North is positive.
         * @param z Move this many steps in z direction. Up is positive.
         */
        MoveCursorCommand(IdPtr commandType, Point::value x, Point::value y, Point::value z);

        void execute(SharedManagerPtr shared) override;
        IdPtr getCommandType() const override;
        void undo(SharedManagerPtr shared) override;

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
     * @brief Create new move cursor command.
     * @param commandType The command type.
     * @param x Move this many steps in x direction. West is positive.
     * @param y Move this many steps in y direction. North is positive.
     * @param z Move this many steps in z direction. Up is positive.
     * @return The command.
     */
    inline CommandPtr makeMoveCursorCommand(IdPtr commandType, Point::value x, Point::value y, Point::value z)
    {
        return std::make_shared<MoveCursorCommand>(commandType, x, y, z);
    }
}

#endif // FRTS_MOVECURSORCOMMAND_H
