#ifndef FRTS_MODELSTARTUP_H
#define FRTS_MODELSTARTUP_H

#include <frts/BaseTickable.h>


namespace frts
{
    /**
     * @brief The model startup executes task before going into the "Run Game"
     *        phase. It should be added to startup modules.
     */
    class ModelStartup : public BaseTickable<Tickable>
    {
    public:
        ModelStartup();

        /**
         * @brief The identifier.
         * @return The id string.
         */
        static std::string identifier()
        {
            return "frts/ModelStartup";
        }

        void checkRequiredData(const SharedManagerPtr& shared) override;
        void tick(const SharedManagerPtr& shared) override;
        void validateModules(const SharedManagerPtr& shared) override;
    };

    /**
     * @brief Create new ModelStartup.
     * @return The model startup.
     */
    inline TickablePtr makeModelStartup()
    {
        return std::make_shared<ModelStartup>();
    }
}

#endif // FRTS_MODELSTARTUP_H
