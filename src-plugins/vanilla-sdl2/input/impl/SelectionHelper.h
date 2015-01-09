#ifndef FRTS_SELECTIONHELPER_H
#define FRTS_SELECTIONHELPER_H

#include <frts/shared>
#include <frts/vanillamodel>

namespace frts
{
    /**
     * @brief End selection.
     * @param shared The shared manager.
     */
    void endSelection(SharedManagerPtr shared);

    /**
     * @brief Start a new selection.
     * @param shared The shared manager.
     */
    void newSelection(SharedManagerPtr shared);

    /**
     * @brief Stop/Cancel selection.
     * @param shared The shared manager.
     */
    void stopSelection(SharedManagerPtr shared);

    /**
     * @brief Update current selection.
     * @param cursorPos The current cursor position.
     * @param shared The shared manager.
     */
    void updateSelection(PointPtr cursorPos, SharedManagerPtr shared);
}

#endif // FRTS_SELECTIONHELPER_H
