#ifndef FRTS_MOVABLEIMPL_H
#define FRTS_MOVABLEIMPL_H

#include <entity/Movable.h>

#include <memory>


namespace frts
{
    class MovableImpl : public Movable
    {
    public:
        /**
         * @param type The component type.
         */
        MovableImpl(IdPtr type);

        IdPtr getComponentType() const override;
        Direction getDirection() const override;
        PathPtr getPath() const override;
        PointPtr getNextPathPos() override;
        PointPtr getPreviousPathPos() const override;
        void setPath(PathPtr path) override;

    private:
        PointPtr current;
        PathPtr path;
        PointPtr previous;
        IdPtr type;
    };

    /**
     * @brief Create new movable component.
     * @param type The component type.
     * @return The component.
     */
    inline MovablePtr makeMovable(IdPtr type)
    {
        return std::make_shared<MovableImpl>(type);
    }
}

#endif // FRTS_MOVABLEIMPL_H
