#ifndef FRTS_SHAREDMANAGERIMPL_H
#define FRTS_SHAREDMANAGERIMPL_H

#include <module/ModulePtr.h>
#include <shared/Id.h>
#include <shared/SharedError.h>
#include <shared/SharedManager.h>

#include <memory>
#include <string>
#include <unordered_map>
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
        explicit SharedManagerImpl(const LogPtr& log);
        ~SharedManagerImpl() override;

        /**
         * @brief Get a list of all data values.
         * @return List of data values.
         */
        std::vector<DataValuePtr> getDataValues() const;

        /**
         * @brief Set current frame.
         * @param frame The frame.
         */
        void setFrame(const FramePtr& frame);

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
        void setUtility(const IdPtr& id, const UtilityPtr& utility);

        DataValuePtr getDataValue(const IdPtr& id) const override;
        const FramePtr getFrame() const override;
        LogPtr getLog() const;
        UtilityPtr getUtility(const IdPtr& id) const override;
        bool isQuitApplication() const override;
        IdPtr makeId(const std::string& str) const override;
        TickableItr renderModulesBegin() const override;
        TickableItr renderModulesEnd() const override;
        void setDataValue(const IdPtr& id, const DataValuePtr& value) override;
        void setQuitApplication(bool quit) override;
        TickableItr updateModulesBegin() const override;
        TickableItr updateModulesEnd() const override;

    private:
        using DataValueMap = std::unordered_map<IdPtr, DataValuePtr>;
        using UtilityModulesMap = std::unordered_map<IdPtr, UtilityPtr>;

    private:
        const std::string logModule = "frts::SharedManager";

        DataValueMap dataValues;
        FramePtr frame;
        LogPtr log;
        std::vector<TickablePtr> renderModules;
        bool quitApplication;
        std::vector<TickablePtr> updateModules;
        UtilityModulesMap utilityModules;

    private:
        IdNotFoundError makeIdNotFoundError(const IdPtr& id) const;
    };

    /**
     * @brief Create new SharedManager.
     * @param log The log.
     * @return The SharedManager.
     */
    inline SharedManagerImplPtr makeSharedManager(const LogPtr& log)
    {
        assert(log != nullptr);

        return std::make_shared<SharedManagerImpl>(log);
    }
}

#endif // FRTS_SHAREDMANAGERIMPL_H
