#ifndef FRTS_MOVESCREENCOMMANDBUILDER_H
#define FRTS_MOVESCREENCOMMANDBUILDER_H

#include <frts/vanillacommand>
#include <frts/vanillamodel>

namespace frts
{
    /**
     * @brief Builder for MoveScreenCommand.
     */
    class MoveScreenCommandBuilder : public CommandBuilder
    {
    public:
        /**
         * @param commandType The command type.
         * @param x Move this many steps in x direction. West is positive.
         * @param y Move this many steps in y direction. North is positive.
         * @param z Move this many steps in z direction. Up is positive.
         */
        MoveScreenCommandBuilder(const IdPtr& commandType, Point::value x, Point::value y, Point::value z);

        CommandPtr build(const SharedManagerPtr& shared) override;

    private:
        IdPtr commandType;

        Point::value x;
        Point::value y;
        Point::value z;
    };

    /**
     * @brief Create new move screen command builder.
     * @param commandType The command type.
     * @param x Move this many steps in x direction. West is positive.
     * @param y Move this many steps in y direction. North is positive.
     * @param z Move this many steps in z direction. Up is positive.
     * @return The command builder.
     */
    inline CommandBuilderPtr makeMoveScreenCommandBuilder(const IdPtr& commandType, Point::value x, Point::value y, Point::value z)
    {
        assert(commandType != nullptr);

        return std::make_shared<MoveScreenCommandBuilder>(commandType, x, y, z);
    }
}

#endif // FRTS_MOVESCREENCOMMANDBUILDER_H
