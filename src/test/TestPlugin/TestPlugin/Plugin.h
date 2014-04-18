#ifndef PLUGIN_H
#define PLUGIN_H

#include <frts/plugin>

#include <string>

class Plugin : public frts::Plugin
{
public:
    Plugin();

    frts::ModulePtr getModule(frts::IdPtr id) noexcept override;

private:
    static const std::string moduleId;
};

#endif // PLUGIN_H
