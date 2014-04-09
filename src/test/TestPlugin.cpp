#include <catch.hpp>

#include <module/Module.h>
#include <module/ModulePtr.h>
#include <plugin/PluginError.h>
#include <plugin/PluginManager.h>
#include <shared/IdImpl.h>

#include <cstdio>
#include <string>

TEST_CASE("Find modules.", "[plugin]")
{
    const std::string path = "";
    const std::string testPlugin = "TestPlugin";
    const std::string testModule = "TestModule";

    SECTION("Find module.")
    {
        frts::PluginManager pluginManager;

        pluginManager.loadPlugin(path, testPlugin);
        frts::IdPtr id = frts::IdPtr(new frts::IdImpl(testModule));
        frts::ModulePtr module = pluginManager.findModule(id);
        REQUIRE(module != nullptr);
        REQUIRE(module->getName() == testModule);

        id = frts::IdPtr(new frts::IdImpl("NotExistingModule"));
        module = pluginManager.findModule(id);
        REQUIRE(module == nullptr);

        REQUIRE_THROWS_AS(pluginManager.loadPlugin(path, "NotExistingPlugin"),
                          frts::LibraryNotFound);
    }
}
