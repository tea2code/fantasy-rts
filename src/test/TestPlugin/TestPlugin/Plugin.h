#ifndef PLUGIN_H
#define PLUGIN_H

#include <plugin/Plugin.h>

#include <string>

class Plugin : public frts::Plugin
{
public:
    Plugin();

    frts::ModulePtr getModule(frts::IdPtr id);

private:
    static const std::string moduleId;
};

#endif // PLUGIN_H
