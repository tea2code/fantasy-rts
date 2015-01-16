#ifndef FRTS_JOBMARKERBUILDER_H
#define FRTS_JOBMARKERBUILDER_H

#include <frts/vanillamodel>


namespace frts
{
    /**
     * @brief Builder for JobMarker component.
     */
    class JobMarkerBuilder : public ComponentBuilder
    {
    public:
        JobMarkerBuilder();
        ~JobMarkerBuilder();

        ComponentPtr build(const SharedManagerPtr& shared) override;
        ComponentPtr build(const SharedManagerPtr& shared, const ConfigNodePtr& node) override;
    };

    /**
     * @brief Create new JobMarkerBuilder.
     * @return The component builder.
     */
    inline ComponentBuilderPtr makeJobMarkerBuilder()
    {
        return std::make_shared<JobMarkerBuilder>();
    }
}

#endif // FRTS_JOBMARKERBUILDER_H
