#ifndef FRTS_BLOCKING_H
#define FRTS_BLOCKING_H

#include <memory>


namespace frts
{
    class Blocking;

    /**
     * @brief Pointer to Blocking.
     */
    using BlockingPtr = std::shared_ptr<Blocking>;

    /**
     * @brief Describes if a entity is blocked or blocking certain types.
     */
    class Blocking
    {
    public:
        virtual ~Blocking() = 0;

        /**
         * @brief Does this object block the other.
         * @param other The other blocking.
         * @return True if this object blocks the other.
         */
        virtual bool blocks(BlockingPtr other) = 0;

        /**
         * @brief Does this object block or is blocked by wall types.
         * @return True if blocking.
         */
        virtual bool wall() const = 0;

        /**
         * @brief Does this object block or is blocked by water types.
         * @return True if blocking.
         */
        virtual bool water() const = 0;
    };
}

#endif // FRTS_BLOCKING_H
