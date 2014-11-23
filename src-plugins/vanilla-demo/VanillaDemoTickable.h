#ifndef FRTS_VANILLADEMOTICKABLE_H
#define FRTS_VANILLADEMOTICKABLE_H

#include <frts/BaseTickable.h>
#include <frts/vanillamodel>


namespace frts
{
    class VanillaDemoTickable : public BaseTickable
    {
    public:
        VanillaDemoTickable();

        /**
         * @brief The default identifier for this module.
         * @return The id string.
         */
        static std::string identifier()
        {
            return "frts/VanillaDemo";
        }

        bool init(SharedManagerPtr shared) override;
        void tick(SharedManagerPtr shared) override;
        void validateModules(SharedManagerPtr shared) override;

    private:
        PointPtr lastCursorPos;
        EntityPtr player;
    };
}

#endif // FRTS_VANILLADEMOTICKABLE_H
