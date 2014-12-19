#ifndef FRTS_SHAREDMANAGER_H
#define FRTS_SHAREDMANAGER_H

#include "SharedPtr.h"
#include <log/Log.h>
#include <module/ModulePtr.h>

#include <cassert>
#include <string>
#include <vector>


namespace frts
{
    /**
     * @brief Iterator to tickable modules.
     */
    using TickableItr = std::vector<TickablePtr>::const_iterator;

    /**
     * @brief Interface representing the shared manager. It gives access
     * to the shared state including data values and other modules.
     */
    class SharedManager
    {
    public:
        virtual ~SharedManager() {}

        /**
         * @brief Get data value.
         * @throws IdNotFoundError if data value with id does not exist.
         * @param id The id of the value.
         * @return The data value.
         */
        virtual DataValuePtr getDataValue(IdPtr id) const = 0;

        /**
         * @brief Get current frame data.
         * @return The frame data.
         */
        virtual const FramePtr getFrame() const = 0;

        /**
         * @brief Get log.
         * @return The log.
         */
        virtual LogPtr getLog() const = 0;

        /**
         * @brief Get utility module.
         * @throws IdNotFoundError if utility with id does not exist.
         * @param id The id of the module.
         * @return The module.
         */
        virtual UtilityPtr getUtility(IdPtr id) const = 0;

        /**
         * @brief Indicates that the application should end.
         * @return True if the application should end else false.
         */
        virtual bool isQuitApplication() const = 0;

        /**
         * @brief Create id from string.
         * @param str The string representing this id.
         * @return The id.
         */
        virtual IdPtr makeId(const std::string& str) const = 0;

        /**
         * @brief Get render modules.
         * @return Iterator to beginning of modules.
         */
        virtual TickableItr renderModulesBegin() const = 0;

        /**
         * @brief Get render modules.
         * @return Iterator to end of modules.
         */
        virtual TickableItr renderModulesEnd() const = 0;

        /**
         * @brief Set data value. Existing values will be overriden.
         * @param id The id of the value.
         * @param value The data value.
         */
        virtual void setDataValue(IdPtr id, DataValuePtr value) = 0;

        /**
         * @brief Set or reset flag to indicate that the application should quit.
         * @param quit If true the application will end.
         */
        virtual void setQuitApplication(bool quit) = 0;

        /**
         * @brief Get update modules.
         * @return Iterator to beginning of modules.
         */
        virtual TickableItr updateModulesBegin() const = 0;

        /**
         * @brief Get update modules.
         * @return Iterator to end of modules.
         */
        virtual TickableItr updateModulesEnd() const = 0;
    };

    /**
     * @brief Get data value from shared.
     * @param shared The shared manager.
     * @param id The data value id.
     * @return The data value.
     */
    template <typename DataValueClass>
    std::shared_ptr<DataValueClass> getDataValue(SharedManagerPtr shared, const std::string& id)
    {
        assert(shared != nullptr);

        return std::static_pointer_cast<DataValueClass>(shared->getDataValue(shared->makeId(id)));
    }

    /**
     * @brief Get utility from shared.
     * @param shared The shared manager.
     * @param id The data value id.
     * @return The utility.
     */
    template <typename UtilityClass>
    std::shared_ptr<UtilityClass> getUtility(SharedManagerPtr shared, const std::string& id)
    {
        assert(shared != nullptr);

        return std::static_pointer_cast<UtilityClass>(shared->getUtility(shared->makeId(id)));
    }
}

#endif // FRTS_SHAREDMANAGER_H
