#ifndef FRTS_MODULEVALIDATION
#define FRTS_MODULEVALIDATION

#include "ModuleError.h"
#include "ModulePtr.h"
#include "Tickable.h"
#include <shared/SharedError.h>
#include <shared/SharedManager.h>

#include <boost/format.hpp>

#include <string>


namespace frts
{
    /**
     * @brief Validate tickable modules.
     * @throws ModuleViolation if no module matches.
     * @param validator Name of the module... executing the validation.
     * @param typeName The type name of the tickable.
     * @param typeVersion The type version.
     * @param shared The shared manager.
     */
    inline void validateTickable(const std::string& validator, const std::string& typeName, int typeVersion, SharedManagerPtr shared)
    {
        auto func = [&](TickableItr begin, TickableItr end)
        {
            bool found = false;
            for (auto it = begin; it != end; ++it)
            {
               auto module = (*it);
               if (module->getTypeName() == typeName)
               {
                   if (module->getTypeVersion() != 1)
                   {
                       auto msg = boost::format(R"(Tickable "%1%" has the wrong version %2%. Version %3% is required. Required by "%4%".)")
                               % typeName % typeVersion % module->getTypeVersion() % validator;
                       throw ModuleViolation(msg.str());
                   }
                   found = true;
                   break;
               }
            }
            return found;
        };

        if (!func(shared->updateModulesBegin(), shared->updateModulesEnd()) &&
            !func(shared->renderModulesBegin(), shared->renderModulesEnd()))
        {
            auto msg = boost::format(R"(Tickable "%1%" not found. Required by "%2%".)") % typeName % validator;
            throw ModuleViolation(msg.str());
        }
    }

    /**
     * @brief Validate utility modules.
     * @throws ModuleViolation if no module matches.
     * @param validator Name of the module... executing the validation.
     * @param utilityId ID of the module.
     * @param typeVersion The type version of the module.
     * @param shared The shared manager.
     */
    inline void validateUtility(const std::string& validator, const std::string& utilityId, int typeVersion, SharedManagerPtr shared)
    {
        try
        {
            auto module = getUtility<Module>(shared, utilityId);
            if (module->getTypeVersion() != typeVersion)
            {
                auto msg = boost::format(R"(Utility "%1%" has the wrong version %2%. Version %3% is required. Required by "%4%".)")
                        % utilityId % typeVersion % module->getTypeVersion() % validator;
                throw ModuleViolation(msg.str());
            }
        }
        catch(const IdNotFoundError&)
        {
            auto msg = boost::format(R"(Utility "%1%" not found. Required by "%2%".)") % utilityId % validator;
            throw ModuleViolation(msg.str());
        }
    }
}

#endif // FRTS_MODULEVALIDATION

