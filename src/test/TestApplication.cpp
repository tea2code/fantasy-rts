#include <catch.hpp>

#include <Application.h>

#include <boost/format.hpp>

#include <fstream>
#include <stdexcept>


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
    file << "    - test/plugin1.dll" << std::endl;
    file << "    - plugin2.dll" << std::endl;
    file << "" << std::endl;
    file << "renderModules:" << std::endl;
    file << "    - test/renderModule1" << std::endl;
    file << "    - renderModule2" << std::endl;
    file << "" << std::endl;
    file << "updateModules:" << std::endl;
    file << "    - test/updateModule1" << std::endl;
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

TEST_CASE("Execute start phases.", "[application]")
{
    setupLoadFile();

    frts::Application app(nullptr);

    SECTION("Read and parse load file")
    {
        frts::Application::LoadConfiguration loadConfig = app.readLoadFile(TEST_APPLICATION_LOAD_FILE);

        REQUIRE(loadConfig.plugins.size() == 2);
        REQUIRE(loadConfig.plugins.at(0) == "test/plugin1.dll");
        REQUIRE(loadConfig.plugins.at(1) == "plugin2.dll");

        REQUIRE(loadConfig.renderModules.size() == 2);
        REQUIRE(loadConfig.renderModules.at(0) == "test/renderModule1");
        REQUIRE(loadConfig.renderModules.at(1) == "renderModule2");

        REQUIRE(loadConfig.updateModules.size() == 2);
        REQUIRE(loadConfig.updateModules.at(0) == "test/updateModule1");
        REQUIRE(loadConfig.updateModules.at(1) == "updateModule2");

        REQUIRE(loadConfig.utilities.size() == 0);

        REQUIRE(loadConfig.configurations.size() == 2);
        REQUIRE(loadConfig.configurations.at(0) == "test/configuration1.yaml");
        REQUIRE(loadConfig.configurations.at(1) == "configuration2.yaml");
    }
}
