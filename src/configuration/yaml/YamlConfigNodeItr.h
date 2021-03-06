#ifndef FRTS_YAMLCONFIGNODEITR_H
#define FRTS_YAMLCONFIGNODEITR_H

#include <configuration/ConfigNodeItr.h>

#include <yaml-cpp/yaml.h>


namespace frts
{
    /**
     * @brief Implementation of ConfigNodeItr using YAML.
     */
    class YamlConfigNodeItr : public ConfigNodeItr
    {
    public:
        explicit YamlConfigNodeItr(YAML::Node::iterator iterator);
        ~YamlConfigNodeItr() override;

        self_type* operator++() override;
        self_type* operator++(int) override;
        reference operator*() override;
        pointer operator->() override;
        bool operator==(const self_type& rhs) override;
        bool operator!=(const self_type& rhs) override;

    private:
        YAML::Node::iterator iterator;
    };
}

#endif // FRTS_YAMLCONFIGNODEITR_H
