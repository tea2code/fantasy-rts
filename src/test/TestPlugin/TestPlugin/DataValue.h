#ifndef DATAVALUE_H
#define DATAVALUE_H

#include <frts/shared>

class DataValue : public frts::DataValue
{
public:
    DataValue();

    std::string getName() const override;
    std::string getTypeName() const override;
    int getTypeVersion() const override;
    int getVersion() const override;
};

#endif // DATAVALUE_H
