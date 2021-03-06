#ifndef FRTS_RENDERABLEIMPL_H
#define FRTS_RENDERABLEIMPL_H

#include <graphic/Renderable.h>


namespace frts
{
    class RenderableImpl : public Renderable
    {
    public:
        RenderableImpl(const IdPtr& type);

        bool doStacking() const override;
        IdPtr getComponentType() const override;
        IdPtr getSprite() const override;
        unsigned int getTransparency() const override;
        unsigned int getSpriteIndex() const override;
        bool isSpriteIndexSet() const override;
        void setSprite(const IdPtr& id) override;
        void setSpriteIndex(unsigned int index) override;
        void setStacking(bool stacking) override;
        void setTransparency(unsigned int transparency) override;

    private:
        IdPtr sprite;
        unsigned int spriteIndex = 0;
        bool spriteIndexSet = false;
        bool stacking = true;
        unsigned int transparency = 0;
        IdPtr type;
    };

    /**
     * @brief Create new Renderable.
     * @return The component.
     */
    inline RenderablePtr makeRenderable(const IdPtr& type)
    {
        assert(type != nullptr);

        return std::make_shared<RenderableImpl>(type);
    }
}

#endif // FRTS_RENDERABLEIMPL_H
