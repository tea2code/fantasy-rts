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
        const FramePtr getFrame() const noexcept override;
        LogPtr getLog() const noexcept;
        UtilityPtr getUtility(IdPtr id) const override;
        IdPtr makeId(const std::string& str) const noexcept override;
        TickableItr renderModulesBegin() const noexcept override;
        TickableItr renderModulesEnd() const noexcept override;
        void setValue(IdPtr id, DataValuePtr value) noexcept override;
        TickableItr updateModulesBegin() const noexcept override;
        TickableItr updateModulesEnd() const noexcept override;

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
