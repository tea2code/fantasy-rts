#ifndef FRTS_RENDERABLEIMPL_H
#define FRTS_RENDERABLEIMPL_H

#include <graphic/Renderable.h>

#include <vector>


namespace frts
{
    class RenderableImpl : public Renderable
    {
    public:
        RenderableImpl(IdPtr type);

        void addSprite(IdPtr id) override;
        IdPtr getComponentType() const override;
        int getNumSprites() const override;
        IdPtr getSprite(int spriteIndex) const override;
        int getSpriteIndex() const override;
        void setSpriteIndex(int index) override;

    private:
        std::vector<IdPtr> sprites;
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
