#ifndef FRTS_BASEJOB_H
#define FRTS_BASEJOB_H

#include <frts/vanillajob>
#include <frts/vanillamodel>


namespace frts
{
    class BaseJob : public Job
    {
    public:
        /**
         * @param jobRequirements List of requirements for the entity which might execute the job.
         * @param jobMarker The job marker entity. Will be removed after completion.
         */
        BaseJob(const IdPtr& id, const IdPtr& type, const IdUnorderedSet& jobRequirements, const EntityPtr& jobMarker);
        ~BaseJob();

        EntityPtr getExecutingEntity() const override;
        Frame::time getDueTime() const override;
        IdPtr getId() const override;
        IdUnorderedSet getRequirements() const override;
        IdPtr getType() const override;
        void setExecutingEntity(const EntityPtr& entity) override;

    protected:
        /**
         * @brief Remove the job marker from region.
         * @param shared The shared manager.
         */
        void clearJobMarker(const SharedManagerPtr& shared);

        /**
         * @brief Set the due time.
         * @param dueTime The due time.
         */
        void setDueTime(Frame::time dueTime);

    private:
        Frame::time dueTime;
        EntityPtr executingEntity;
        IdPtr id;
        IdUnorderedSet jobRequirements;
        IdPtr type;

        /**
         * @todo Replace with weak pointer?
         * @warning Must be set to null after removale from region to prevent possible memory leak.
         */
        EntityPtr jobMarker;

    };
}

#endif // FRTS_BASEJOB_H
