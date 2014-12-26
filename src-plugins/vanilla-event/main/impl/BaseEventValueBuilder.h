#ifndef FRTS_BASEEVENTVALUEBUILDER
#define FRTS_BASEEVENTVALUEBUILDER

#include <main/EventValueBuilder.h>

#include <frts/shared>


namespace frts
{
    /**
     * @brief Base implementation of event value builders.
     */
    template<class EventValue>
    class BaseEventValueBuilder : public EventValueBuilder
    {
    public:
        BaseEventValueBuilder(IdPtr type)
            : type{type}
        {}

        EventValuePtr build(SharedManagerPtr) override
        {
            return std::make_shared<EventValue>(type);
        }

    private:
        IdPtr type;
    };
}

#endif // FRTS_BASEEVENTVALUEBUILDER

