#ifndef FRTS_MODELFACTORY_H
#define FRTS_MODELFACTORY_H

#include <region/Point.h>

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

        
        virtual PointPtr makePoint(Point::value x, Point::value y, Point::value z) = 0;
    };
}

#endif // FRTS_MODELFACTORY_H
