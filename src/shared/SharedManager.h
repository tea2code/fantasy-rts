#ifndef SHAREDMANAGER_H
#define SHAREDMANAGER_H

#include "DataValue.h"
#include "Frame.h"
#include "Id.h"
#include <log/Log.h>
#include <module/ModulePtr.h>

#include <memory>
#include <string>
#include <vector>


namespace frts
{
    class SharedManager;

    /**
     * @brief Pointer to SharedManager.
     */
    using SharedManagerPtr = std::shared_ptr<SharedManager>;

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
        virtual void setValue(IdPtr id, DataValuePtr value) = 0;

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
}

#endif // SHAREDMANAGER_H
