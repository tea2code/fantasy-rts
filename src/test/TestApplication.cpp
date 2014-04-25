#include <catch.hpp>

#include <log/ConsoleLog.h>
#include <main/Application.h>
#include <module/ModuleError.h>
#include <module/ModulePtr.h>
#include <module/Tickable.h>
#include <module/Utility.h>
#include <plugin/PluginPtr.h>
#include <shared/DataValue.h>
#include <shared/impl/IdImpl.h>
#include <shared/impl/SharedManagerImpl.h>

#include <boost/format.hpp>

#include <fstream>
#include <stdexcept>
#include <vector>


namespace TestApp
{
    #define TEST_APPLICATION_LOAD_FILE "load.yaml"

    void setupLoadFile()
    {
        std::ofstream file(TEST_APPLICATION_LOAD_FILE);
        if(!file)
        {
            auto msg = boost::format(R"(Cannot open/create file "%1%".)") % TEST_APPLICATION_LOAD_FILE;
            throw std::runtime_error(msg.str());
        }
        file << "plugins:" << std::endl;
        file << "    - test/plugin1" << std::endl;
        file << "    - plugin2" << std::endl;
        file << "" << std::endl;
        file << "renderModules:" << std::endl;
        file << "    - renderModule1" << std::endl;
        file << "    - renderModule2" << std::endl;
        file << "" << std::endl;
        file << "updateModules:" << std::endl;
        file << "    - updateModule1" << std::endl;
        file << "    - updateModule2" << std::endl;
        file << "" << std::endl;
        file << "utilities:" << std::endl;
        file << "    # No utilities." << std::endl;
        file << "" << std::endl;
        file << "configurations:" << std::endl;
        file << "    - test/configuration1.yaml" << std::endl;
        file << "    - configuration2.yaml" << std::endl;
        file.close();
    }

    #define TEST_CONFIGURATION_CONFIG_FILE "configuration.yaml"

    void setupConfiguration()
    {
        std::ofstream file(TEST_CONFIGURATION_CONFIG_FILE);
        if(!file)
        {
            auto msg = boost::format(R"(Cannot open/create file "%1%".)") % TEST_CONFIGURATION_CONFIG_FILE;
            throw std::runtime_error(msg.str());
        }
        file << "ConfigKey1:" << std::endl;
        file << "    key: value" << std::endl;
        file << "ConfigKey2:" << std::endl;
        file << "    key: value" << std::endl;
        file << "ConfigKey3:" << std::endl;
        file << "    key: value" << std::endl;
        file.close();
    }
}

TEST_CASE("Execute start phases.", "[application]")
{
    TestApp::setupLoadFile();

    frts::Application app(nullptr);

    SECTION("Phase 1: Read load configuration.")
    {
        frts::Application::LoadConfiguration loadConfig = app.readLoadFile(TEST_APPLICATION_LOAD_FILE);

        REQUIRE(loadConfig.plugins.size() == 2);
        REQUIRE(loadConfig.plugins.at(0) == "test/plugin1");
        REQUIRE(loadConfig.plugins.at(1) == "plugin2");

        REQUIRE(loadConfig.renderModules.size() == 2);
        REQUIRE(loadConfig.renderModules.at(0) == "renderModule1");
        REQUIRE(loadConfig.renderModules.at(1) == "renderModule2");

        REQUIRE(loadConfig.updateModules.size() == 2);
        REQUIRE(loadConfig.updateModules.at(0) == "updateModule1");
        REQUIRE(loadConfig.updateModules.at(1) == "updateModule2");

        REQUIRE(loadConfig.utilities.size() == 0);

        REQUIRE(loadConfig.configurations.size() == 2);
        REQUIRE(loadConfig.configurations.at(0) == "test/configuration1.yaml");
        REQUIRE(loadConfig.configurations.at(1) == "configuration2.yaml");
    }

    SECTION("Phase 2: Load plugins.")
    {
        const std::string rootPath = "";
        std::vector<std::string> pluginPaths = {"TestPlugin"};

        REQUIRE_NOTHROW(app.loadPlugins(rootPath, pluginPaths));

        SECTION("Phase 3: Get modules.")
        {
            // Execute as sub section of phase 2 because we need the TestPlugin
            // to be loaded to find modules.

            std::vector<std::string> tickableNames = {"TestTickable"};
            std::string utilityName = "TestUtility";

            std::vector<frts::TickablePtr> tickableModules = app.findTickables(tickableNames);

            REQUIRE(tickableModules.size() == 1);
            REQUIRE(tickableModules.at(0).get() != nullptr);
            REQUIRE(tickableModules.at(0)->getName() == "TestTickable");

            frts::IdPtr id = frts::makeId(utilityName);
            frts::UtilityPtr utilityModule = app.findUtility(id);
            REQUIRE(utilityModule.get() != nullptr);
            REQUIRE(utilityModule->getName() == "TestUtility");

            frts::LogPtr log = std::make_shared<frts::ConsoleLog>();
            frts::SharedManagerImplPtr shared = std::make_shared<frts::SharedManagerImpl>(log);
            std::vector<frts::ModulePtr> utilityModules = {utilityModule};
            std::vector<frts::ModulePtr> updateModules;
            for (auto& module : tickableModules)
            {
                updateModules.push_back(module);
            }

            std::vector<frts::ModulePtr> modules = updateModules;
            modules.push_back(utilityModule);

            // Execute the following sub sections after phase 3 because we need
            // the modules of TestPlugin.

            SECTION("Phase 4: Check required modules.")
            {
                REQUIRE_NOTHROW(app.validateRequiredModules(updateModules, shared));
                REQUIRE_THROWS_AS(app.validateRequiredModules(utilityModules, shared),
                                  frts::ModuleViolation);
            }

            SECTION("Phase 5: Create data.")
            {
                REQUIRE_NOTHROW(app.createData(updateModules, shared));
                REQUIRE_NOTHROW(app.createData(utilityModules, shared));

                frts::IdPtr dataId = shared->makeId("TestDataValue");
                frts::DataValuePtr data = shared->getDataValue(dataId);
                REQUIRE(data.get() != nullptr);
                REQUIRE(data->getName() == "TestDataValue");
            }

            SECTION("Phase 6: Register main config keys.")
            {
                auto supportedKeys = app.registerConfigKeys(modules);
                REQUIRE(supportedKeys.size() == 3);
                REQUIRE(supportedKeys.at("ConfigKey1").size() == 2);
                REQUIRE(supportedKeys.at("ConfigKey2").size() == 1);
                REQUIRE(supportedKeys.at("ConfigKey3").size() == 1);

                SECTION("Phase 7: Read config.")
                {
                    // Execute the following sub sections after phase 6 because we need
                    // the config keys.

                    TestApp::setupConfiguration();
                    std::vector<std::string> configFiles = {TEST_CONFIGURATION_CONFIG_FILE};

                    REQUIRE_NOTHROW(app.readConfig(supportedKeys, shared, "", configFiles));
                }
            }

            SECTION("Phase 8: Validate data.")
            {
                REQUIRE_NOTHROW(app.validateData(updateModules, shared));
                REQUIRE_THROWS_AS(app.validateData(utilityModules, shared),
                                  frts::DataViolation);
            }

            SECTION("Phase 9: Initialize modules.")
            {
                REQUIRE_NOTHROW(app.init(modules, shared));
            }
        }
    }
}
