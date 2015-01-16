#ifndef FRTS_BASETICKABLE_H
#define FRTS_BASETICKABLE_H

#include <frts/module>
#include <frts/shared>

#include <string>


namespace frts
{
    /**
     * @brief Base implementation of tickables.
     */
    template<class TickableInterface>
    class BaseTickable : public TickableInterface
    {
    public:
        BaseTickable(const std::string& name, int version, const std::string& typeName, int typeVersion)
            : name{name}, version{version}, typeName{typeName}, typeVersion{typeVersion}
        {}
        
        virtual void checkRequiredData(const SharedManagerPtr&) override
        {}

        virtual bool createData(const SharedManagerPtr&) override
        {
            return false;
        }

        virtual std::string getName() const override
        {
            return name;
        }

        virtual std::vector<std::string> getSupportedConfig() override
        {
            return {};
        }

        virtual std::string getTypeName() const override
        {
            return typeName;
        }

        virtual int getTypeVersion() const override
        {
            return typeVersion;
        }

        virtual int getVersion() const override
        {
            return version;
        }

        virtual bool init(const SharedManagerPtr&) override
        {
            isInit = true;
            return false;
        }

        bool isInitialized() const override
        {
            return isInit;
        }

        bool isPreInitialized() const override
        {
            return isPreInit;
        }

        virtual void parseConfig(const std::string&, const ConfigNodePtr&, const SharedManagerPtr&) override
        {}

        virtual bool preInit(const SharedManagerPtr&) override
        {
            isPreInit = true;
            return false;
        }

        virtual void validateData(const SharedManagerPtr&) override
        {}

        virtual void validateModules(const SharedManagerPtr&) override
        {}

    private:
        bool isInit = false;
        bool isPreInit = false;
        std::string name;
        int version;
        std::string typeName;
        int typeVersion;
    };
}

#endif // FRTS_BASETICKABLE_H
