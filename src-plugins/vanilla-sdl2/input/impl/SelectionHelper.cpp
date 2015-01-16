#include "SelectionHelper.h"

#include <graphic/GraphicData.h>
#include <input/SelectionData.h>
#include <main/Sdl2Ids.h>

#include <frts/vanillaevent>


namespace
{
void raiseEvent(const std::string& eventId, frts::PointVector selection, frts::SharedManagerPtr shared)
{
    auto em = frts::getUtility<frts::EventManager>(shared, frts::EventIds::eventManager());
    auto event = em->makeEvent(shared->makeId(eventId), shared);
    auto eventValue = frts::makeEventValue<frts::PointListEventValue>(em, frts::ModelEventIds::pointListEventValue(), shared);
    eventValue->setValue(selection);
    event->setValue(shared->makeId(frts::Sdl2Ids::selectionEventValue()), eventValue);
    em->raise(event, shared);
}
}

void frts::endSelection(const SharedManagerPtr& shared)
{
    assert(shared != nullptr);

    auto gd = getDataValue<GraphicData>(shared, Sdl2Ids::graphicData());
    auto sd = getDataValue<SelectionData>(shared, Sdl2Ids::selectionData());
    auto rm = getDataValue<RegionManager>(shared, ModelIds::regionManager());

    assert(sd->isSelecting());

    auto cursorPos = rm->getPos(gd->getCursor(), shared);
    sd->setSelectionEnd(cursorPos);

    auto selection = sd->getSelection(shared);
    stopSelection(shared);

    // Raise selection finished event.
    raiseEvent(Sdl2Ids::selectionFinishedEvent(), selection, shared);
}

void frts::newSelection(const SharedManagerPtr& shared)
{
    assert(shared != nullptr);

    auto gd = getDataValue<GraphicData>(shared, Sdl2Ids::graphicData());
    auto sd = getDataValue<SelectionData>(shared, Sdl2Ids::selectionData());
    auto rm = getDataValue<RegionManager>(shared, ModelIds::regionManager());

    assert(!sd->isSelecting());

    sd->setIsSelecting(true);

    auto cursorPos = rm->getPos(gd->getCursor(), shared);
    sd->setSelectionStart(cursorPos);

    updateSelection(cursorPos, shared);
}

void frts::stopSelection(const SharedManagerPtr& shared)
{
    assert(shared != nullptr);

    auto sd = getDataValue<SelectionData>(shared, Sdl2Ids::selectionData());
    auto rm = getDataValue<RegionManager>(shared, ModelIds::regionManager());

    assert(sd->isSelecting());

    // Remove all selection highlighting entities.
    auto entities = sd->getSelectionEntities();
    for (auto& entity : entities)
    {
        rm->removeEntity(entity, shared);
    }

    sd->resetSelection();
}

void frts::updateSelection(const PointPtr& cursorPos, const SharedManagerPtr& shared)
{
    assert(cursorPos != nullptr);
    assert(shared != nullptr);

    auto mf = getUtility<ModelFactory>(shared, ModelIds::modelFactory());
    auto sd = getDataValue<SelectionData>(shared, Sdl2Ids::selectionData());
    auto rm = getDataValue<RegionManager>(shared, ModelIds::regionManager());

    assert(sd->isSelecting());

    sd->setSelectionEnd(cursorPos);

    // Get the old selection entities and prepare list of new selection entities. We separate
    // these two because we can reuse the old ones. This has a huge performance impact because
    // creating entities has some costs and the number of entities created can quickly increase
    // during an selection.
    auto oldEntities = sd->getSelectionEntities();
    EntityVector::size_type index = 0;
    EntityVector entities;

    // Set selection highlight entities.
    auto selection = sd->getSelection(shared);
    for (auto& pos : selection)
    {
        // Recycle old entities.
        EntityPtr entity;
        if (index < oldEntities.size())
        {
            entity = oldEntities.at(index);
            index += 1;
        }
        else
        {
            entity = mf->makeEntity(sd->getSelectionEntityId(), shared);
        }
        entities.push_back(entity);
        rm->setPos(entity, pos, shared);
    }
    sd->setSelectionEntities(entities);

    // If the selection has shrinked there are some old entities left which must be removed.
    for (; index < oldEntities.size(); ++index)
    {
        rm->removeEntity(oldEntities.at(index), shared);
    }

    // Raise selection changed event.
    raiseEvent(Sdl2Ids::selectionChangedEvent(), selection, shared);
}
