#include "Application.h"

#include <configuration/ConfigNode.h>
#include <configuration/yaml/YamlConfigParser.h>
#include <module/Module.h>
#include <module/ModuleError.h>
#include <module/Tickable.h>
#include <module/Utility.h>
#include <shared/impl/IdImpl.h>

#include <algorithm>
#include <string>


namespace
{
    frts::DeadLockError makeDeadLockError(const std::string& function, const std::vector<frts::ModulePtr>& modules)
    {
        std::string msg = "Application: Possible dead lock while executing " + function + " was "
                          "detected. Following modules where involved: ";
        for (auto& module : modules)
        {
            msg += module->getName();
            msg += ", ";
        }
        if (!modules.empty())
        {
            msg = msg.substr(0, msg.size() - 2);
        }

        return frts::DeadLockError(msg);
    }
}


frts::Application::Application(LogPtr log)
    : log{log}
{
}

void frts::Application::checkRequiredDataValues(const std::vector<ModulePtr>& modules, SharedManagerPtr shared) const
{
    for (auto& module : modules)
    {
        module->checkRequiredData(shared);
    }
}

void frts::Application::createData(const std::vector<ModulePtr>& modules, SharedManagerPtr shared) const
{
    auto todo = modules;
    std::vector<ModulePtr> repeat;
    unsigned int count = 1;
    while (!todo.empty())
    {
        for(auto& module : todo)
        {
            if (module->createData(shared))
            {
                repeat.push_back(module);
            }
        }
        todo = repeat;
        repeat.clear();

        if (count >= maxNumberExtraExecutions)
        {
            throw makeDeadLockError("createData()", todo);
        }
        count += 1;
    }
}

void frts::Application::executeModules(const std::vector<TickablePtr>& modules, SharedManagerPtr shared) const
{
    for(auto& module : modules)
    {
        module->tick(shared);
    }
}

std::vector<frts::TickablePtr> frts::Application::findTickables(const std::vector<std::string>& moduleNames)
{
    std::vector<TickablePtr> result;
    for(const auto& moduleName : moduleNames)
    {
        auto id = makeId(moduleName);
        auto module = std::dynamic_pointer_cast<Tickable>(pluginManager.findModule(id));
        result.push_back(module);
    }
    return result;
}

frts::UtilityPtr frts::Application::findUtility(IdPtr id)
{
    return std::dynamic_pointer_cast<Utility>(pluginManager.findModule(id));
}

void frts::Application::init(const std::vector<ModulePtr>& modules, SharedManagerPtr shared) const
{
    auto todo = modules;
    std::vector<ModulePtr> repeat;
    unsigned int count = 1;
    while (!todo.empty())
    {
        for(auto& module : todo)
        {
            if (module->init(shared))
            {
                repeat.push_back(module);
            }
        }
        todo = repeat;
        repeat.clear();

        if (count >= maxNumberExtraExecutions)
        {
            throw makeDeadLockError("init()", todo);
        }
        count += 1;
    }
}

void frts::Application::loadPlugins(const std::string& rootPath, const std::vector<std::string>& pluginPaths)
{
    for(const auto& pluginPath : pluginPaths)
    {
        // Normalize path.
        auto path = rootPath + pluginPath;
        std::replace(path.begin(), path.end(), '\\', '/');

        // Split path into path and library name.
        std::string name;
        auto index = path.find_last_of('/');
        if (index != std::string::npos)
        {
            index += 1;
            name = path.substr(index, path.size() - index);
            path = path.substr(0, index);
        }
        else
        {
            name = path;
            path = "";
        }

        // Load plugin.
        pluginManager.loadPlugin(path, name);
    }
}

void frts::Application::preInit(const std::vector<ModulePtr>& modules, SharedManagerPtr shared) const
{
    auto todo = modules;
    std::vector<ModulePtr> repeat;
    unsigned int count = 1;
    while (!todo.empty())
    {
        for(auto& module : todo)
        {
            if (module->preInit(shared))
            {
                repeat.push_back(module);
            }
        }
        todo = repeat;
        repeat.clear();

        if (count >= maxNumberExtraExecutions)
        {
            throw makeDeadLockError("preInit()", todo);
        }
        count += 1;
    }
}

void frts::Application::readConfig(const std::map<std::string, std::vector<ModulePtr>>& supportedKeys,
                                   SharedManagerPtr shared,
                                   const std::string& rootPath,
                                   const std::vector<std::string>& configFiles) const
{
    assert(shared != nullptr);

    YamlConfigParser parser;

    for (const auto& configFile : configFiles)
    {
        // Parse file.
        auto node = parser.parseFile(rootPath + configFile);

        // Check if config node contains supported keys.
        for (auto it = supportedKeys.begin(); it != supportedKeys.end(); ++it)
        {
            // Node has key.
            if (node->has(it->first))
            {
                auto keyNode = node->getNode(it->first);

                // Give every associated module chance to parse node.
                for (auto& module : it->second)
                {
                    module->parseConfig(it->first, keyNode, shared);
                }
            }
        }
    }
}

frts::Application::LoadConfiguration frts::Application::readLoadFile(const std::string& filePath) const
{
    YamlConfigParser parser;
    auto node = parser.parseFile(filePath);

    LoadConfiguration result;
    result.plugins = node->getStrings("plugins");
    result.renderModules = node->getStrings("renderModules");
    result.shutdownModules = node->getStrings("shutdownModules");
    result.startupModules = node->getStrings("startupModules");
    result.updateModules = node->getStrings("updateModules");
    result.utilities = node->getStrings("utilities");
    result.configurations = node->getStrings("configurations");
    return result;
}

std::map<std::string, std::vector<frts::ModulePtr>> frts::Application::registerConfigKeys(const std::vector<ModulePtr>& modules) const
{
    std::map<std::string, std::vector<frts::ModulePtr>> result;
    for (auto& module : modules)
    {
        auto configKeys = module->getSupportedConfig();
        for (auto& key : configKeys)
        {
            result[key].push_back(module);
        }
    }
    return result;
}

void frts::Application::setMaxNumberExtraExecutions(unsigned int num)
{
    maxNumberExtraExecutions = num;
}

void frts::Application::validateData(const std::vector<ModulePtr>& modules, SharedManagerPtr shared) const
{
    assert(shared != nullptr);

    for (auto& module : modules)
    {
        module->validateData(shared);
    }
}

void frts::Application::validateRequiredModules(const std::vector<ModulePtr>& modules, SharedManagerPtr shared) const
{
    assert(shared != nullptr);

    for (auto& module : modules)
    {
        module->validateModules(shared);
    }
}
