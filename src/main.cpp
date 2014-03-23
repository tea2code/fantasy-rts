#ifndef UNIT_TEST

#include "Application.h"

#include <iostream>
#include <string>

int main()
{
    // Most basic configuration.
    const std::string loadFile = "plugins/load.yaml";

    // Start application.
    frts::Application app;
    frts::Application::LoadConfiguration loadConfig = app.readLoadFile(loadFile);

    // All done. Good night.
    std::cin.ignore();
    return 0;
}

#else

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#endif
