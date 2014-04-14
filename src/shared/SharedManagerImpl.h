#ifndef SHAREDMANAGERIMPL_H
#define SHAREDMANAGERIMPL_H

#include "DataValue.h"
#include "Frame.h"
#include "Id.h"
#include "SharedError.h"
#include "SharedManager.h"
#include <module/Tickable.h>
#include <module/Utility.h>

#include <map>
#include <memory>
#include <string>
#include <vector>


namespace frts
{
    class SharedManagerImpl;

    /**
     * @brief Pointer to SharedManagerImpl.
     */
    using SharedManagerImplPtr = std::shared_ptr<SharedManagerImpl>;

    class SharedManagerImpl : public SharedManager
    {
    public:
        SharedManagerImpl(LogPtr log,
                          std::vector<frts::TickablePtr> renderModules,
                          std::vector<frts::TickablePtr> updateModules);
        ~SharedManagerImpl() override;

        /**
         * @brief Set current frame.
         * @param frame The frame.
         */
        void setFrame(FramePtr frame);

        /**
         * @brief Set utility module
         * @param id The id of the module.
         * @param utility The module.
         */
        void setUtility(IdPtr id, UtilityPtr utility);

        DataValuePtr getDataValue(IdPtr id) const override;
        const FramePtr getFrame() const override;
        LogPtr getLog() const;
        UtilityPtr getUtility(IdPtr id) const override;
        IdPtr makeId(const std::string& str) const override;
        TickableItr renderModulesBegin() const override;
        TickableItr renderModulesEnd() const override;
        void setValue(IdPtr id, DataValuePtr value) override;
        TickableItr updateModulesBegin() const override;
        TickableItr updateModulesEnd() const override;

    private:
        std::map<IdPtr, DataValuePtr> dataValues;
        FramePtr frame;
        LogPtr log;
        std::vector<TickablePtr> renderModules;
        std::vector<TickablePtr> updateModules;
        std::map<IdPtr, UtilityPtr> utilityModules;

    private:
        IdNotFoundError makeIdNotFoundError(IdPtr id) const;
    };
}

#endif // SHAREDMANAGERIMPL_H
