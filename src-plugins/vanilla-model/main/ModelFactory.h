#ifndef FRTS_MODELFACTORY_H
#define FRTS_MODELFACTORY_H

#include <frts/module>

namespace frts
{
    class ModelFactory;

    /**
     * @brief Pointer to ModelFactory.
     */
    using ModelFactoryPtr = std::shared_ptr<ModelFactory>;

    /**
     * @brief Model factory is a utility which allows creation of several
     * model types like pointer or entities.
     */
    class ModelFactory : public Utility
    {
    public:
        virtual ~ModelFactory() {}
    };
}

#endif // FRTS_MODELFACTORY_H
