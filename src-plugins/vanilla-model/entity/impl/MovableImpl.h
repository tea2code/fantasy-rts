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
        MovableImpl(const IdPtr& type);

        IdPtr getComponentType() const override;
        Direction getDirection() const override;
        PathPtr getPath() const override;
        PointPtr getNextPathPos() override;
        PointPtr getPreviousPathPos() const override;
        double getSpeed() const override;
        void setPath(const PathPtr& path) override;
        void setSpeed(double speed) override;

    private:
        PointPtr current;
        PathPtr path;
        PointPtr previous;
        double speed = 0.0;
        IdPtr type;
    };

    /**
     * @brief Create new movable component.
     * @param type The component type.
     * @return The component.
     */
    inline MovablePtr makeMovable(const IdPtr& type)
    {
        assert(type != nullptr);

        return std::make_shared<MovableImpl>(type);
    }
}

#endif // FRTS_MOVABLEIMPL_H
