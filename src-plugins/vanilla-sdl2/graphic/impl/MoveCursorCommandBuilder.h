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
        MoveCursorCommandBuilder(const IdPtr& commandType, Point::value x, Point::value y, Point::value z);

        CommandPtr build(const SharedManagerPtr& shared) override;

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
    inline CommandBuilderPtr makeMoveCursorCommandBuilder(const IdPtr& commandType, Point::value x, Point::value y, Point::value z)
    {
        assert(commandType != nullptr);

        return std::make_shared<MoveCursorCommandBuilder>(commandType, x, y, z);
    }
}

#endif // FRTS_MOVECURSORCOMMANDBUILDER_H
