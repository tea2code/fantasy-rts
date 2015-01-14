#ifndef FRTS_VANILLADEMOTICKABLE_H
#define FRTS_VANILLADEMOTICKABLE_H

#include <frts/BaseTickable.h>
#include <frts/vanillamodel>
#include <frts/vanillaevent>

#include <memory>
#include <string>
#include <vector>


namespace frts
{
    class VanillaDemoTickable : public BaseTickable, public EventObserver, public std::enable_shared_from_this<EventObserver>
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

        void checkRequiredData(SharedManagerPtr shared) override;
        bool init(SharedManagerPtr shared) override;
        void notify(EventPtr event, SharedManagerPtr shared) override;
        void tick(SharedManagerPtr shared) override;
        void validateModules(SharedManagerPtr shared) override;

    private:
        EntityVector highlights;

        EntityVector lazy;
        EntityVector working;

    private:
        void addHighlight(ModelFactoryPtr modelFactory, RegionManagerPtr regionManager,
                          SharedManagerPtr shared, PointPtr pos, const std::string& id);
        void resetHighlights(RegionManagerPtr regionManager, SharedManagerPtr shared);
    };
}

#endif // FRTS_VANILLADEMOTICKABLE_H
