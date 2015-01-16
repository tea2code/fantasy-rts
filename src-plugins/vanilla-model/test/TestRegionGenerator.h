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
        SimpleTestRegionGenerator(const frts::IdPtr& blockingType, const frts::IdPtr& sortOrderType)
            : blockingType{blockingType}, sortOrderType{sortOrderType}
        {}

        std::string getSupportedConfig() const override
        {
            return {};
        }

        void init(const frts::SharedManagerPtr&) override
        { }

        frts::WriteableBlockPtr newBlock(const frts::PointPtr&, const frts::SharedManagerPtr&) override
        {
            return frts::makeBlock(blockingType, sortOrderType);
        }

        void parseConfig(const frts::ConfigNodePtr&, const frts::SharedManagerPtr&) override
        {}

        void validateData(const frts::SharedManagerPtr&) override
        {}

    private:
        frts::IdPtr blockingType;
        frts::IdPtr sortOrderType;
    };

    inline frts::RegionGeneratorPtr makeSimpleTestRegionGenerator(const frts::IdPtr& blockingType, const frts::IdPtr& sortOrderType)
    {
        return std::make_shared<SimpleTestRegionGenerator>(blockingType, sortOrderType);
    }
}

#endif // TESTREGIONGENERATOR

