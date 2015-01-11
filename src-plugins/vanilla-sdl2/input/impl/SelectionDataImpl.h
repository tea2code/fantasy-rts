#ifndef FRTS_SELECTIONDATAIMPL_H
#define FRTS_SELECTIONDATAIMPL_H

#include <input/SelectionData.h>


namespace frts
{
    class SelectionDataImpl : public SelectionData
    {
    public:
        SelectionDataImpl();
        ~SelectionDataImpl();

        std::string getName() const override;
        std::string getTypeName() const override;
        int getTypeVersion() const override;
        int getVersion() const override;

        PointVector getSelection(SharedManagerPtr shared) const override;
        PointPtr getSelectionEnd() const override;
        IdPtr getSelectionEntityId() const override;
        EntityVector getSelectionEntities() const override;
        PointPtr getSelectionStart() const override;
        bool isSelecting() const override;
        void resetSelection() override;
        void setIsSelecting(bool isSelecting) override;
        void setSelectionEnd(PointPtr pos) override;
        void setSelectionEntityId(IdPtr entityId) override;
        void setSelectionEntities(EntityVector entities) override;
        void setSelectionStart(PointPtr pos) override;

    private:
        PointPtr start;
        PointPtr end;

        IdPtr selectionEntityId;

        EntityVector selectionEntities;

        bool currentlySelecting = false;
    };

    /**
     * @brief Create new SelectionData.
     * @return The SelectionData.
     */
    inline SelectionDataPtr makeSelectionData()
    {
        return std::make_shared<SelectionDataImpl>();
    }
}

#endif // FRTS_SELECTIONDATAIMPL_H
