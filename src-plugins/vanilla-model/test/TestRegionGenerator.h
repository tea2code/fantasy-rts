#ifndef TESTREGIONGENERATOR
#define TESTREGIONGENERATOR

#include <regiongenerator/RegionGenerator.h>
#include <region/impl/BlockImpl.h>

#include <memory>


namespace test
{
    class SimpleTestRegionGenerator : public frts::RegionGenerator
    {
    public:
        SimpleTestRegionGenerator(frts::IdPtr blockingType, frts::IdPtr sortOrderType)
            : blockingType{blockingType}, sortOrderType{sortOrderType}
        {}

        frts::WriteableBlockPtr newBlock(frts::PointPtr, frts::SharedManagerPtr)
        {
            return frts::makeBlock(blockingType, sortOrderType);
        }

    private:
        frts::IdPtr blockingType;
        frts::IdPtr sortOrderType;
    };

    inline frts::RegionGeneratorPtr makeSimpleTestRegionGenerator(frts::IdPtr blockingType, frts::IdPtr sortOrderType)
    {
        return std::make_shared<SimpleTestRegionGenerator>(blockingType, sortOrderType);
    }
}

#endif // TESTREGIONGENERATOR

