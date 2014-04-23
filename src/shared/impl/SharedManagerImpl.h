#ifndef FRTS_SHAREDMANAGERIMPL_H
#define FRTS_SHAREDMANAGERIMPL_H

#include <module/ModulePtr.h>
#include <shared/SharedError.h>
#include <shared/SharedManager.h>

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
        SharedManagerImpl(LogPtr log);
        ~SharedManagerImpl() override;

        /**
         * @brief Set current frame.
         * @param frame The frame.
         */
        void setFrame(FramePtr frame) noexcept;

        /**
         * @brief Set render modules
         * @param modules The modules.
         */
        void setRenderModules(const std::vector<frts::TickablePtr>& modules) noexcept;

        /**
         * @brief Set update modules
         * @param modules The modules.
         */
        void setUpdateModules(const std::vector<frts::TickablePtr>& modules) noexcept;

        /**
         * @brief Set utility module
         * @param id The id of the module.
         * @param utility The module.
         */
        void setUtility(IdPtr id, UtilityPtr utility) noexcept;

        DataValuePtr getDataValue(IdPtr id) const override;
        const FramePtr getFrame() const noexcept override;
        LogPtr getLog() const noexcept;
        UtilityPtr getUtility(IdPtr id) const override;
        IdPtr makeId(const std::string& str) const noexcept override;
        TickableItr renderModulesBegin() const noexcept override;
        TickableItr renderModulesEnd() const noexcept override;
        void setDataValue(IdPtr id, DataValuePtr value) noexcept override;
        TickableItr updateModulesBegin() const noexcept override;
        TickableItr updateModulesEnd() const noexcept override;

    private:
        static const std::string logModule;

        std::map<std::string, DataValuePtr> dataValues;
        FramePtr frame;
        LogPtr log;
        std::vector<TickablePtr> renderModules;
        std::vector<TickablePtr> updateModules;
        std::map<std::string, UtilityPtr> utilityModules;

    private:
        IdNotFoundError makeIdNotFoundError(IdPtr id) const;
    };
}

#endif // FRTS_SHAREDMANAGERIMPL_H
