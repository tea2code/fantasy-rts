#ifndef YAMLCONFIGNODEITR_H
#define YAMLCONFIGNODEITR_H

#include <configuration/ConfigNodeItr.h>


namespace frts
{
    /**
     * @brief Implementation of ConfigNodeItr using YAML.
     */
    class YamlConfigNodeItr : public ConfigNodeItr
    {
    public:
        YamlConfigNodeItr();
        ~YamlConfigNodeItr();

        self_type* operator++();
        self_type* operator++(int);
        reference operator*();
        pointer operator->();
        bool operator==(const self_type& rhs);
        bool operator!=(const self_type& rhs);
    };
}

#endif // YAMLCONFIGNODEITR_H
