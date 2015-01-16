#ifndef FRTS_JOBMARKER
#define FRTS_JOBMARKER

#include "Job.h"
#include <frts/vanillamodel>

#include <memory>


namespace frts
{
    class JobMarker;

    /**
     * @brief Pointer to JobMarker.
     */
    using JobMarkerPtr = std::shared_ptr<JobMarker>;

    /**
     * @brief Simple marker for runnings jobs at world positions.
     */
    class JobMarker : public Component
    {
    public:
        virtual ~JobMarker() {}

        /**
         * @brief Get the job of this marker.
         * @return The job.
         */
        virtual JobPtr getJob() const = 0;

        /**
         * @brief Set the job of this marker.
         * @param job The job.
         */
        virtual void setJob(const JobPtr& job) = 0;
    };
}

#endif // FRTS_JOBMARKER

