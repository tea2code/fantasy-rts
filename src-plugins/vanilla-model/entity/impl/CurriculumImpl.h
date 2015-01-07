#ifndef FRTS_CURRICULUMIMPL_H
#define FRTS_CURRICULUMIMPL_H

#include <entity/Curriculum.h>

#include <memory>


namespace frts
{
    class CurriculumImpl : public Curriculum
    {
    public:
        /**
         * @param type The component type.
         */
        CurriculumImpl(IdPtr type);
        ~CurriculumImpl();

        void addAbility(IdPtr ability) override;
        IdUnorderedSet getAbilities() const override;
        IdPtr getComponentType() const override;
        bool hasAbility(IdPtr ability) const override;
        void removeAbility(IdPtr ability) override;

    private:
        IdUnorderedSet abilities;
        IdPtr type;
    };

    /**
     * @brief Create new Curriculum.
     * @param type The component type.
     * @return The Curriculum.
     */
    inline CurriculumPtr makeCurriculum(IdPtr type)
    {
        assert(type != nullptr);

        return std::make_shared<CurriculumImpl>(type);
    }
}

#endif // FRTS_CURRICULUMIMPL_H
