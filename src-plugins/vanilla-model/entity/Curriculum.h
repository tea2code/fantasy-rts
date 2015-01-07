#ifndef FRTS_CURRICULUM
#define FRTS_CURRICULUM

#include "Component.h"

#include <frts/shared>

#include <memory>


namespace frts
{
    class Curriculum;

    /**
     * @brief Pointer to Curriculum.
     */
    using CurriculumPtr = std::shared_ptr<Curriculum>;

    /**
     * @brief Gives a description of the abilities of an entity. Can be used to determine if an
     *        entity can execude an task.
     */
    class Curriculum : public Component
    {
    public:
        virtual ~Curriculum() {}

        /**
         * @brief Add a new ability. Adding multiple times will add it only once.
         * @param ability The ability.
         */
        virtual void addAbility(IdPtr ability) = 0;

        /**
         * @brief Get all abilities.
         * @return List of abilities.
         */
        virtual IdUnorderedSet getAbilities() const = 0;

        /**
         * @brief Check if this entity has the given ability.
         * @param ability The ability.
         * @return True if this entity has the given ability else false.
         */
        virtual bool hasAbility(IdPtr ability) const = 0;

        /**
         * @brief Remove an ability. Removing multiple times isn't any problem
         * @param ability The ability.
         */
        virtual void removeAbility(IdPtr ability) = 0;
    };
}

#endif // FRTS_CURRICULUM

