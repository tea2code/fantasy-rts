#include "DataValue.h"

DataValue::DataValue()
{
}

std::string DataValue::getName() const
{
    return "TestDataValue";
}

std::string DataValue::getTypeName() const
{
    return getName();
}

int DataValue::getTypeVersion() const
{
    return getVersion();
}

int DataValue::getVersion() const
{
    return 1;
}
