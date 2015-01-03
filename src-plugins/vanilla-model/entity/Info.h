#ifndef FRTS_INFO
#define FRTS_INFO

#include "Component.h"

#include <frts/shared>

#include <memory>
#include <utility>
#include <vector>


namespace frts
{
    class Info;

    /**
     * @brief Pointer to Info.
     */
    using InfoPtr = std::shared_ptr<Info>;

    /**
     * @brief Component with additional information about an entity.
     */
    class Info : public Component
    {
    public:
        /**
         * @brief An info item consisting of key and value in a pair.
         */
        using InfoItem = std::pair<IdPtr, IdPtr>;

    public:
        virtual ~Info() {}

        /**
         * @brief Get information values in their order.
         * @return A list of information items.
         */
        virtual std::vector<InfoItem> getInformation() const = 0;

        /**
         * @brief Set information values.
         * @param values A list of information items.
         */
        virtual void setInformation(std::vector<InfoItem> values) = 0;
    };
}

#endif // FRTS_INFO

