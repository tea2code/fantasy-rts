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

    /**
     * @brief Implementation of SharedManager.
     */
    class SharedManagerImpl : public SharedManager
    {
    public:
        SharedManagerImpl(LogPtr log);
        ~SharedManagerImpl() override;

        /**
         * @brief Set current frame.
         * @param frame The frame.
         */
        void setFrame(FramePtr frame);

        /**
         * @brief Set render modules
         * @param modules The modules.
         */
        void setRenderModules(const std::vector<frts::TickablePtr>& modules);

        /**
         * @brief Set update modules
         * @param modules The modules.
         */
        void setUpdateModules(const std::vector<frts::TickablePtr>& modules);

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
        bool isQuitApplication() const override;
        IdPtr makeId(const std::string& str) const override;
        TickableItr renderModulesBegin() const override;
        TickableItr renderModulesEnd() const override;
        void setDataValue(IdPtr id, DataValuePtr value) override;
        void setQuitApplication(bool quit) override;
        TickableItr updateModulesBegin() const override;
        TickableItr updateModulesEnd() const override;

    private:
        static const std::string logModule;

        std::map<std::string, DataValuePtr> dataValues;
        FramePtr frame;
        LogPtr log;
        std::vector<TickablePtr> renderModules;
        bool quitApplication;
        std::vector<TickablePtr> updateModules;
        std::map<std::string, UtilityPtr> utilityModules;

    private:
        IdNotFoundError makeIdNotFoundError(IdPtr id) const;
    };
}

#endif // FRTS_SHAREDMANAGERIMPL_H
