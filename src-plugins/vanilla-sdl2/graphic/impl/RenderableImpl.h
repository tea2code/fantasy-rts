#ifndef FRTS_RENDERABLEIMPL_H
#define FRTS_RENDERABLEIMPL_H

#include <graphic/Renderable.h>


namespace frts
{
    class RenderableImpl : public Renderable
    {
    public:
        RenderableImpl(IdPtr type);

        IdPtr getComponentType() const override;
        IdPtr getSprite() const override;
        int getSpriteIndex() const override;
        void setSprite(IdPtr id) override;
        void setSpriteIndex(int index) override;

    private:
        IdPtr sprite;
        int spriteIndex;
        IdPtr type;
    };

    /**
     * @brief Create new Renderable.
     * @return The component.
     */
    inline RenderablePtr makeRenderable(IdPtr type)
    {
        return std::make_shared<RenderableImpl>(type);
    }
}

#endif // FRTS_RENDERABLEIMPL_H
