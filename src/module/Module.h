#ifndef FRTS_MODULE_H
#define FRTS_MODULE_H

#include <configuration/ConfigNodeItr.h>
#include <shared/SharedManager.h>

#include <memory>
#include <string>
#include <vector>


namespace frts
{
    /**
     * @brief Base interface for modules.
     */
    class Module
    {
    public:
        virtual ~Module() {}

        /**
         * @brief Create data value objects.
         * @param shared The shared manager.
         */
        virtual void createData(SharedManagerPtr shared) = 0;

        /**
         * @brief Get the module name.
         * @return The name of the module.
         */
        virtual std::string getName() const = 0;

        /**
         * @brief Get the keys of all supported configuration nodes.
         * @return List of supported keys.
         */
        virtual std::vector<std::string> getSupportedConfig() = 0;

        /**
         * @brief Initialize the module.
         * @param shared The shared manager.
         */
        virtual void init(SharedManagerPtr shared) = 0;

        /**
         * @brief Parse the given configuration node.
         * @param node The configuration node.
         * @param shared The shared manager.
         */
        virtual void parseConfig(ConfigNodePtr node, SharedManagerPtr shared) = 0;

        /**
         * @brief Validate the current data values.
         * @throws DataViolation if a data value is invalid.
         * @param shared The shared manager.
         */
        virtual void validateData(SharedManagerPtr shared) = 0;

        /**
         * @brief Validate the existing modules.
         * @throws ModuleViolation if a module is invalid.
         * @param shared The shared manager.
         */
        virtual void validateModules(SharedManagerPtr shared) = 0;
    };
}

#endif // FRTS_MODULE_H
