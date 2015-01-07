#ifndef FRTS_CURRICULUMBUILDER_H
#define FRTS_CURRICULUMBUILDER_H

#include <entity/ComponentBuilder.h>


namespace frts
{
    /**
     * @brief Builder for curriculum components.
     */
    class CurriculumBuilder : public ComponentBuilder
    {
    public:
        CurriculumBuilder();
        ~CurriculumBuilder();

        ComponentPtr build(SharedManagerPtr shared) override;
        ComponentPtr build(SharedManagerPtr shared, ConfigNodePtr node) override;
    };

    /**
     * @brief Create new curriculum builder.
     * @return The component builder.
     */
    inline ComponentBuilderPtr makeCurriculumBuilder()
    {
        return std::make_shared<CurriculumBuilder>();
    }
}

#endif // FRTS_CURRICULUMBUILDER_H
