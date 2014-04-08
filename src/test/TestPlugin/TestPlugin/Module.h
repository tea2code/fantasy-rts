#ifndef MODULE_H
#define MODULE_H

#include <module/Module.h>

class Module : public frts::Module
{
public:
    Module();

    void createData(frts::SharedManagerPtr shared);
    std::string getName() const;
    std::vector<std::string> getSupportedConfig();
    void init(frts::SharedManagerPtr shared);
    void parseConfig(frts::ConfigNodePtr node, frts::SharedManagerPtr shared);
    void validateData(frts::SharedManagerPtr shared);
    void validateModules(frts::SharedManagerPtr shared);
};

#endif // MODULE_H
