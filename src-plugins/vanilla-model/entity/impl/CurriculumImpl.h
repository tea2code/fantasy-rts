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
        CurriculumImpl(const IdPtr& type);
        ~CurriculumImpl();

        void addAbility(const IdPtr& ability) override;
        IdUnorderedSet getAbilities() const override;
        IdPtr getComponentType() const override;
        bool hasAbility(const IdPtr& ability) const override;
        void removeAbility(const IdPtr& ability) override;

    private:
        IdUnorderedSet abilities;
        IdPtr type;
    };

    /**
     * @brief Create new Curriculum.
     * @param type The component type.
     * @return The Curriculum.
     */
    inline CurriculumPtr makeCurriculum(const IdPtr& type)
    {
        assert(type != nullptr);

        return std::make_shared<CurriculumImpl>(type);
    }
}

#endif // FRTS_CURRICULUMIMPL_H
