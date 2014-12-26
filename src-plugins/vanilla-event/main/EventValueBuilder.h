#ifndef FRTS_EVENTVALUEBUILDER
#define FRTS_EVENTVALUEBUILDER

#include "EventValue.h"
#include <frts/shared>

#include <memory>


namespace frts
{
    class EventValueBuilder;

    /**
     * @brief Pointer to EventValueBuilder.
     */
    using EventValueBuilderPtr = std::shared_ptr<EventValueBuilder>;

    /**
     * @brief Builder for event values.
     */
    class EventValueBuilder
    {
    public:
        virtual ~EventValueBuilder() {}

        /**
         * @brief Create a new event value.
         * @param shared The shared manager.
         * @return The event value.
         */
        virtual EventValuePtr build(SharedManagerPtr shared) = 0;
    };
}

#endif // FRTS_EVENTVALUEBUILDER

