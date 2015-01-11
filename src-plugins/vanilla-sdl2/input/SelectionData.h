#ifndef FRTS_SELECTIONDATA
#define FRTS_SELECTIONDATA

#include <frts/vanillamodel>
#include <frts/shared>

#include <memory>
#include <vector>


namespace frts
{
    class SelectionData;

    /**
     * @brief Pointer to SelectionData.
     */
    using SelectionDataPtr = std::shared_ptr<SelectionData>;

    /**
     * @brief The selection data contains all the informations to the current selection.
     */
    class SelectionData : public DataValue
    {
    public:
        virtual ~SelectionData() {}

        /**
         * @brief Get the current selection.
         * @param shared The shared manager.
         * @return The current selection as a point list.
         */
        virtual PointVector getSelection(SharedManagerPtr shared) const = 0;

        /**
         * @brief Get the end position of the current selection.
         * @return The end position or null.
         */
        virtual PointPtr getSelectionEnd() const = 0;

        /**
         * @brief Get the selection marker entity id.
         * @return The id.
         */
        virtual IdPtr getSelectionEntityId() const = 0;

        /**
         * @brief Get the selection marker entities if available.
         * @return A list of selection marker entities.
         */
        virtual EntityVector getSelectionEntities() const = 0;

        /**
         * @brief Get the start position of the current selection.
         * @return The start position or null.
         */
        virtual PointPtr getSelectionStart() const = 0;

        /**
         * @brief Check if currently a selection is active.
         * @return True if currently a selection is active else false.
         */
        virtual bool isSelecting() const = 0;

        /**
         * @brief Reset/Invalidad the current selection. This will also remove any selection entities.
         */
        virtual void resetSelection() = 0;

        /**
         * @brief Set if currently a selection is active.
         * @param isSelecting The current selection state.
         */
        virtual void setIsSelecting(bool isSelecting) = 0;

        /**
         * @brief Set the end position of the current selection.
         * @param pos The end position.
         */
        virtual void setSelectionEnd(PointPtr pos) = 0;

        /**
         * @brief Set the selection marker entity id.
         * @param entityId The id.
         */
        virtual void setSelectionEntityId(IdPtr entityId) = 0;

        /**
         * @brief Set the current selection marker entities.
         * @param entities The entities.
         */
        virtual void setSelectionEntities(EntityVector entities) = 0;

        /**
         * @brief Set the start position of the current selection.
         * @param pos The start position.
         */
        virtual void setSelectionStart(PointPtr pos) = 0;
    };
}

#endif // FRTS_SELECTIONDATA

