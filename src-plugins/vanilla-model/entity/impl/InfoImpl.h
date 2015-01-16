#ifndef FRTS_INFOIMPL_H
#define FRTS_INFOIMPL_H

#include <entity/Info.h>


namespace frts
{
    class InfoImpl : public Info
    {
    public:
        /**
         * @param type The component type.
         */
        InfoImpl(const IdPtr& type);

        IdPtr getComponentType() const override;
        std::vector<InfoItem> getInformation() const override;
        void setInformation(const std::vector<InfoItem>& values) override;

    private:
        std::vector<InfoItem> information;
        IdPtr type;
    };

    /**
     * @brief Create new Info.
     * @param type The component type.
     * @return The component.
     */
    inline InfoPtr makeInfo(const IdPtr& type)
    {
        return std::make_shared<InfoImpl>(type);
    }
}

#endif // FRTS_INFOIMPL_H
