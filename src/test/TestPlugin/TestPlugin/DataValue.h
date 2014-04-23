#ifndef DATAVALUE_H
#define DATAVALUE_H

#include <frts/shared>

class DataValue : public frts::DataValue
{
public:
    DataValue();

    std::string getName() const noexcept override;
};

#endif // DATAVALUE_H
