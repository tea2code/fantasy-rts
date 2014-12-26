#ifndef FRTS_BASEEVENTVALUE
#define FRTS_BASEEVENTVALUE

#include <frts/shared>


namespace frts
{
    /**
     * @brief Base implementation of event values.
     */
    template<typename T, class I>
    class BaseEventValue : public I
    {
    public:
        BaseEventValue(IdPtr type)
            : type{type}
        {}

        IdPtr getType() const override
        {
            return type;
        }

        T getValue() const override
        {
            return value;
        }

        void setValue(T value) override
        {
            this->value = value;
        }

    private:
        IdPtr type;
        T value;
    };
}

#endif // FRTS_BASEEVENTVALUE

