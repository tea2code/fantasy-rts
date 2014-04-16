#ifndef FRTS_CONFIGNODEPTR_H
#define FRTS_CONFIGNODEPTR_H

#include <memory>


namespace frts
{
    class ConfigNode;

    /**
     * @brief Pointer to ConfigNodes.
     */
    using ConfigNodePtr = std::unique_ptr<ConfigNode>;
}

#endif // FRTS_CONFIGNODEPTR_H
