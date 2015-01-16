#ifndef FRTS_MODULE_H
#define FRTS_MODULE_H

#include <configuration/ConfigNodePtr.h>
#include <shared/SharedPtr.h>

#include <memory>
#include <string>
#include <vector>


namespace frts
{
    class ConfigNodeItr;

    /**
     * @brief Base interface for modules.
     */
    class Module
    {
    public:
        virtual ~Module() {}

        /**
         * @brief Check for required data values. Executed during "Check Required
         *        Data" phase.
         * @throws DataViolation if a data value is missing or invalid.
         * @param shared The shared manager.
         */
        virtual void checkRequiredData(const SharedManagerPtr& shared) = 0;

        /**
         * @brief Create data value objects. Executed during "Create Data" phase.
         * @param shared The shared manager.
         * @return True if another execution of this method is requested else false.
         */
        virtual bool createData(const SharedManagerPtr& shared) = 0;

        /**
         * @brief Get the module name.
         * @return The name of the module.
         */
        virtual std::string getName() const = 0;

        /**
         * @brief Get the keys of all supported configuration nodes. Executed
         *        during "Register Main Config Keys" phase.
         * @return List of supported keys.
         */
        virtual std::vector<std::string> getSupportedConfig() = 0;

        /**
         * @brief Get the module type name.
         * @return The name of the module type.
         */
        virtual std::string getTypeName() const = 0;

        /**
         * @brief Get the module type version.
         * @return Version number of the module type.
         */
        virtual int getTypeVersion() const = 0;

        /**
         * @brief Get the module version.
         * @return Version number of the module.
         */
        virtual int getVersion() const = 0;

        /**
         * @brief Initialize the module. Executed during "Initialize Modules" phase.
         * @param shared The shared manager.
         * @return True if another execution of this method is requested else false.
         */
        virtual bool init(const SharedManagerPtr& shared) = 0;

        /**
         * @brief Indicates if module is initialized. Must return true after init()
         *        is successfully finished.
         * @return True if init() is finished else false.
         */
        virtual bool isInitialized() const = 0;

        /**
         * @brief Indicates if module is preinitialized. Must return true after init()
         *        is successfully finished.
         * @return True if preInit() is finished else false.
         */
        virtual bool isPreInitialized() const = 0;

        /**
         * @brief Parse the given configuration node. Executed during "Read Config"
         *        phase.
         * @param key The key of this node.
         * @param node The configuration node.
         * @param shared The shared manager.
         */
        virtual void parseConfig(const std::string& key, const ConfigNodePtr& node, const SharedManagerPtr& shared) = 0;

        /**
         * @brief Preinitialize the module. Executed during "Preinitialize Modules"
         *        phase.
         * @param shared The shared manager.
         * @return True if another execution of this method is requested else false.
         */
        virtual bool preInit(const SharedManagerPtr& shared) = 0;

        /**
         * @brief Validate the current data values. Executed during "Validate Data"
         *        phase.
         * @throws DataViolation if a data value is invalid.
         * @param shared The shared manager.
         */
        virtual void validateData(const SharedManagerPtr& shared) = 0;

        /**
         * @brief Validate the existing modules. Executed during "Check Required
         *        Modules" phase.
         * @throws ModuleViolation if a module is invalid.
         * @param shared The shared manager.
         */
        virtual void validateModules(const SharedManagerPtr& shared) = 0;
    };
}

#endif // FRTS_MODULE_H
