#ifndef FRTS_JOBMARKERIMPL_H
#define FRTS_JOBMARKERIMPL_H

#include <main/JobMarker.h>

#include <memory>


namespace frts
{
    class JobMarkerImpl : public JobMarker
    {
    public:
        /**
         * @param componentType The component type.
         */
        JobMarkerImpl(IdPtr componentType);
        ~JobMarkerImpl();

        IdPtr getComponentType() const override;
        JobPtr getJob() const override;
        void setJob(JobPtr job) override;

    private:
        IdPtr componentType;
        JobPtr job;
    };

    /**
     * @brief Create new JobMarker.
     * @param componentType The component type.
     * @return The component.
     */
    inline ComponentPtr makeJobMarker(IdPtr componentType)
    {
        assert(componentType != nullptr);

        return std::make_shared<JobMarkerImpl>(componentType);
    }
}

#endif // FRTS_JOBMARKERIMPL_H
