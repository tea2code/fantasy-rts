#ifndef FRTS_BASETICKABLE_H
#define FRTS_BASETICKABLE_H

#include <frts/module>

#include <string>


namespace frts
{
    /**
     * @brief Base implementation of tickables.
     */
    class BaseTickable : public Tickable
    {
    public:
        BaseTickable(const std::string& name, int version, const std::string& typeName, int typeVersion)
            : name{name}, version{version}, typeName{typeName}, typeVersion{typeVersion}
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
            return false;
        }

        virtual void parseConfig(const std::string&, ConfigNodePtr, SharedManagerPtr) override
        {}

        virtual bool preInit(SharedManagerPtr) override
        {
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
    };
}

#endif // FRTS_BASETICKABLE_H
