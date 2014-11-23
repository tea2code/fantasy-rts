#ifndef FRTS_MOVABLEBUILDER_H
#define FRTS_MOVABLEBUILDER_H

#include <entity/ComponentBuilder.h>

#include <string>


namespace frts
{
    class MovableBuilder : public ComponentBuilder
    {
    public:
        MovableBuilder();

        ComponentPtr build(SharedManagerPtr shared) override;
        ComponentPtr build(SharedManagerPtr shared, ConfigNodePtr node) override;
    };

    /**
     * @brief Create new MovableBuilder.
     * @return The MovableBuilder.
     */
    inline ComponentBuilderPtr makeMovableBuilder()
    {
        return std::make_shared<MovableBuilder>();
    }
}

#endif // FRTS_MOVABLEBUILDER_H
