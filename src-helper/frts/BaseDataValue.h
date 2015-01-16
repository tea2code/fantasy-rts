#ifndef FRTS_BASEDATAVALUE_H
#define FRTS_BASEDATAVALUE_H

#include <frts/shared>

#include <string>


namespace frts
{
    /**
     * @brief Base implementation of data values.
     */
    template <class DataValueInterface>
    class BaseDataValue : public DataValueInterface
    {
    public:
        BaseDataValue(const std::string& name, int version, const std::string& typeName, int typeVersion)
            : name{name}, version{version}, typeName{typeName}, typeVersion{typeVersion}
        {}

        virtual std::string getName() const override
        {
            return name;
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

    private:
        std::string name;
        int version;
        std::string typeName;
        int typeVersion;
    };
}

#endif // FRTS_BASEDATAVALUE_H
