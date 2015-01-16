#ifndef FRTS_MODELRESETER_H
#define FRTS_MODELRESETER_H

#include <frts/BaseTickable.h>

#include <memory>


namespace frts
{
    /**
     * @brief The model reseter handles model related clean up at the end of each
     *        frame. It should be placed as the last render module.
     *        Currently the following resets are done:
     *        - Reset changed positions.
     */
    class ModelReseter : public BaseTickable<Tickable>
    {
    public:
        ModelReseter();

        /**
         * @brief The identifier.
         * @return The id string.
         */
        static std::string identifier()
        {
            return "frts/ModelReseter";
        }

        void tick(SharedManagerPtr shared) override;
        void validateModules(SharedManagerPtr shared) override;
    };

    /**
     * @brief Create new ModelReseter.
     * @return The model reseter.
     */
    inline TickablePtr makeModelReseter()
    {
        return std::make_shared<ModelReseter>();
    }
}

#endif // FRTS_MODELRESETER_H
