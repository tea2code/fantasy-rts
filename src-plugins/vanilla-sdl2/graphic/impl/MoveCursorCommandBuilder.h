#ifndef FRTS_MOVECURSORCOMMANDBUILDER_H
#define FRTS_MOVECURSORCOMMANDBUILDER_H

#include <frts/vanillacommand>
#include <frts/vanillamodel>

namespace frts
{
    /**
     * @brief Builder for MoveCursorCommand.
     */
    class MoveCursorCommandBuilder : public CommandBuilder
    {
    public:
        /**
         * @param commandType The command type.
         * @param x Move this many steps in x direction. West is positive.
         * @param y Move this many steps in y direction. North is positive.
         * @param z Move this many steps in z direction. Up is positive.
         */
        MoveCursorCommandBuilder(IdPtr commandType, Point::value x, Point::value y, Point::value z);

        CommandPtr build(SharedManagerPtr shared) override;

    private:
        IdPtr commandType;

        Point::value x;
        Point::value y;
        Point::value z;
    };

    /**
     * @brief Create new move cursor command builder.
     * @param commandType The command type.
     * @param x Move this many steps in x direction. West is positive.
     * @param y Move this many steps in y direction. North is positive.
     * @param z Move this many steps in z direction. Up is positive.
     * @return The command builder.
     */
    inline CommandBuilderPtr makeMoveCursorCommandBuilder(IdPtr commandType, Point::value x, Point::value y, Point::value z)
    {
        return std::make_shared<MoveCursorCommandBuilder>(commandType, x, y, z);
    }
}

#endif // FRTS_MOVECURSORCOMMANDBUILDER_H
