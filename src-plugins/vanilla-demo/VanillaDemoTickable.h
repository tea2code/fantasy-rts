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
    class VanillaDemoTickable : public BaseTickable<Tickable>, public EventObserver, public std::enable_shared_from_this<EventObserver>
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

        void checkRequiredData(const SharedManagerPtr& shared) override;
        bool init(const SharedManagerPtr& shared) override;
        void notify(const EventPtr& event, const SharedManagerPtr& shared) override;
        void tick(const SharedManagerPtr& shared) override;
        void validateModules(const SharedManagerPtr& shared) override;

    private:
        EntityVector highlights;

        EntityVector lazy;
        EntityVector working;

    private:
        void addHighlight(const ModelFactoryPtr& modelFactory, const RegionManagerPtr& regionManager,
                          const SharedManagerPtr& shared, const PointPtr& pos, const std::string& id);
        void resetHighlights(const RegionManagerPtr& regionManager, const SharedManagerPtr& shared);
    };
}

#endif // FRTS_VANILLADEMOTICKABLE_H
