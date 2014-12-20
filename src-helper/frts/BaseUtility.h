#ifndef FRTS_BASEUTILITY_H
#define FRTS_BASEUTILITY_H

#include <frts/module>

#include <string>


namespace frts
{
    /**
     * @brief Base implementation of utilities.
     */
    class BaseUtility : public Utility
    {
    public:
        BaseUtility(const std::string& name, int version, const std::string& typeName, int typeVersion)
            : name{name}, version{version}, typeName{typeName}, typeVersion{typeVersion}
        {}
        
        virtual void checkRequiredData(SharedManagerPtr) override
        {}

        virtual bool createData(SharedManagerPtr) override
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

        virtual bool init(SharedManagerPtr) override
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

        virtual void parseConfig(const std::string&, ConfigNodePtr, SharedManagerPtr) override
        {}

        virtual bool preInit(SharedManagerPtr) override
        {
            isPreInit = true;
            return false;
        }

        virtual void validateData(SharedManagerPtr) override
        {}

        virtual void validateModules(SharedManagerPtr) override
        {}

    private:
        std::string name;
        int version;
        std::string typeName;
        int typeVersion;

    protected:
        bool isInit = false;
        bool isPreInit = false;
    };
}

#endif // FRTS_BASEUTILITY_H
