#include <catch.hpp>

#include <module/Module.h>
#include <module/ModulePtr.h>
#include <plugin/PluginError.h>
#include <plugin/PluginManager.h>
#include <shared/impl/IdImpl.h>

#include <cstdio>
#include <memory>
#include <string>

TEST_CASE("Find modules.", "[plugin]")
{
    const std::string path = "";
    const std::string testPlugin = "TestPlugin";
    const std::string testModule = "TestTickable";

    SECTION("Find module.")
    {
        /* For this test to work you must first compile the sub project
         * TestPlugin in the folder test/TestPlugin/TestPlugin. Copy the
         * generated library  into the directory test/TestPlugin.
         */

        frts::PluginManager pluginManager;
        pluginManager.loadPlugin(path, testPlugin);
        frts::IdPtr id = frts::makeId(testModule);
        frts::ModulePtr module = pluginManager.findModule(id);
        REQUIRE(module != nullptr);
        REQUIRE(module->getName() == testModule);

        id = frts::makeId("NotExistingModule");
        REQUIRE_THROWS_AS(pluginManager.findModule(id), frts::ModuleNotFound);

        REQUIRE_THROWS_AS(pluginManager.loadPlugin(path, "NotExistingPlugin"),
                          frts::LibraryNotFound);
    }
}
