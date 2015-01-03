#include "SidebarDrawer.h"

#include <main/Sdl2Ids.h>

#include <frts/shared>
#include <frts/vanillamodel>
#include <frts/timer.h>

#include <boost/format.hpp>

#include <algorithm>


frts::SidebarDrawer::SidebarDrawer()
    : eventsNextUpdate{fromMilliseconds(0)}, eventsUpdateTime{fromMilliseconds(0)},
      infoNextUpdate{fromMilliseconds(0)}, infoUpdateTime{fromMilliseconds(0)}
{}

frts::SidebarDrawer::~SidebarDrawer()
{
    eventTexture.reset();
}

void frts::SidebarDrawer::drawRectangle(GraphicData::pixel x, GraphicData::pixel y, GraphicData::pixel width, GraphicData::pixel height,
                                        std::uint8_t r, std::uint8_t g, std::uint8_t b)
{
    SDL_Rect rectToRender = {
        static_cast<int>(x),
        static_cast<int>(y),
        static_cast<int>(width),
        static_cast<int>(height)
    };
    SDL_SetRenderDrawColor(drawer->getRenderer().get(), r, g, b, 0);
    SDL_RenderFillRect(drawer->getRenderer().get(), &rectToRender);
}

void frts::SidebarDrawer::drawSeparationLine(GraphicData::pixel startX, GraphicData::pixel endX, GraphicData::pixel y)
{
    SDL_SetRenderDrawColor(drawer->getRenderer().get(), lineColorR, lineColorG, lineColorB, 0);
    SDL_RenderDrawLine(drawer->getRenderer().get(), startX, y, endX, y);
}

frts::Drawer::TexturePtr frts::SidebarDrawer::drawText(const std::string& text, int x, int y, int maxWidth, int maxHeight, SharedManagerPtr shared)
{
    Drawer::TexturePtr texture = nullptr;

    SDL_Surface* surface = TTF_RenderText_Blended_Wrapped(font.get(), text.c_str(), fontColor, maxWidth);
    if(surface == nullptr)
    {
        auto msg = boost::format(R"(TTF_RenderText_Blended_Wrapped Error: %1%)") % TTF_GetError();
        shared->getLog()->error(getName(), msg.str());
        return texture;
    }

    auto width = surface->w;

    auto fontHeight = TTF_FontHeight(font.get());
    int height = (surface->h / fontHeight) * fontHeight;
    while (height > maxHeight)
    {
        height -= fontHeight;
    }

    texture = std::shared_ptr<SDL_Texture>(
        SDL_CreateTextureFromSurface(drawer->getRenderer().get(), surface),
        Drawer::Sdl2Deleter()
    );
    SDL_FreeSurface(surface);
    if(texture == nullptr)
    {
        auto msg = boost::format(R"(SDL_CreateTextureFromSurface Error: %1%)") % SDL_GetError();
        shared->getLog()->error(getName(), msg.str());
        return texture;
    }

    // Draw background.
    drawRectangle(x, y, maxWidth, maxHeight, backgroundR, backgroundG, backgroundB);

    // Draw text.
    SDL_Rect rectToRender = {
        x,
        y,
        width,
        height
    };
    SDL_Rect clip = {
        0,
        0,
        width,
        height
    };
    SDL_RenderCopy(drawer->getRenderer().get(), texture.get(), &clip, &rectToRender);

    return texture;
}

std::string frts::SidebarDrawer::getName() const
{
    return "frts::SidebarDrawer";
}

frts::IdVector frts::SidebarDrawer::getSidebarEvents() const
{
    assert(initialized);

    IdVector result;
    for (auto& kv : eventSubscriptions)
    {
        result.push_back(kv.first);
    }
    return result;
}

void frts::SidebarDrawer::init(DrawerPtr drawer, SharedManagerPtr shared)
{
    assert(drawer != nullptr);
    assert(shared != nullptr);

    // Set drawer.
    this->drawer = drawer;

    // Read font.
    font = std::unique_ptr<TTF_Font, Drawer::Sdl2Deleter>(
        TTF_OpenFont(fontPath.c_str(), fontSize),
        Drawer::Sdl2Deleter()
    );
    if (font == nullptr)
    {
        auto msg = boost::format(R"(Opening font "%1%" with size %2% failed: %3%)")
                % fontPath % fontSize % TTF_GetError();
        shared->getLog()->error(getName(), msg.str());
        return;
    }

    // Supported event values.
    eventValueBool = shared->makeId(EventIds::booleanEventValue());
    eventValueFloat = shared->makeId(EventIds::floatEventValue());
    eventValueInteger = shared->makeId(EventIds::integerEventValue());
    eventValueId = shared->makeId(EventIds::idEventValue());
    eventValueString = shared->makeId(EventIds::stringEventValue());
    eventValuePoint = shared->makeId(ModelEventIds::pointEventValue());
    eventValueEntity = shared->makeId(ModelEventIds::entityEventValue());

    initialized = true;
}

void frts::SidebarDrawer::notify(EventPtr event, SharedManagerPtr shared)
{
    assert(event != nullptr);
    assert(shared != nullptr);

    events.push_front(event);
    eventsChanged = true;
}

void frts::SidebarDrawer::setSidebarConfig(SharedManagerPtr shared, ConfigNodePtr sidebarNode)
{
    assert(shared != nullptr);
    assert(sidebarNode != nullptr);

    auto md = getDataValue<MainData>(shared, MainIds::mainData());

    if (sidebarNode->has("background"))
    {
        auto rgbNode = sidebarNode->getNode("background");
        backgroundR = rgbNode->getInteger("r", backgroundR);
        backgroundG = rgbNode->getInteger("g", backgroundG);
        backgroundB = rgbNode->getInteger("b", backgroundB);
    }

    eventsHeight = sidebarNode->getInteger("events-height", eventsHeight);

    if (sidebarNode->has("events-update"))
    {
        eventsUpdateTime = fromMilliseconds(sidebarNode->getInteger("events-update"));
    }

    if (sidebarNode->has("font-color"))
    {
        auto rgbNode = sidebarNode->getNode("font-color");
        fontColor.r = rgbNode->getInteger("r", fontColor.r);
        fontColor.g = rgbNode->getInteger("g", fontColor.g);
        fontColor.b = rgbNode->getInteger("b", fontColor.b);
    }

    if (sidebarNode->has("font-path"))
    {
        fontPath = md->getPluginPath() + sidebarNode->getString("font-path");
    }

    fontSize = sidebarNode->getInteger("font-size", fontSize);

    infoOnlyWithComponent = sidebarNode->getBool("info-only-with-component", infoOnlyWithComponent);

    infoText = sidebarNode->getString("info-text", infoText);

    infoTextHeight = sidebarNode->getInteger("info-text-height", infoTextHeight);

    if (sidebarNode->has("info-update"))
    {
        infoUpdateTime = fromMilliseconds(sidebarNode->getInteger("info-update"));
    }

    if (sidebarNode->has("line-color"))
    {
        auto rgbNode = sidebarNode->getNode("line-color");
        lineColorR = rgbNode->getInteger("r", lineColorR);
        lineColorG = rgbNode->getInteger("g", lineColorG);
        lineColorB = rgbNode->getInteger("b", lineColorB);
    }

    padding = sidebarNode->getInteger("padding", padding);

    if (sidebarNode->has("tile-background"))
    {
        auto rgbNode = sidebarNode->getNode("tile-background");
        tileBackgroundR = rgbNode->getInteger("r", tileBackgroundR);
        tileBackgroundG = rgbNode->getInteger("g", tileBackgroundG);
        tileBackgroundB = rgbNode->getInteger("b", tileBackgroundB);
    }

    tileZoom = sidebarNode->getInteger("tile-zoom", tileZoom);

    if (sidebarNode->has("events"))
    {
        auto eventsNode = sidebarNode->getNode("events");
        for (auto node : *eventsNode)
        {
            auto type = shared->makeId(node->getString("type"));
            EventSubscription subscription;
            subscription.text = node->getString("text");
            for(auto& value : node->getStrings("values"))
            {
                subscription.eventValues.push_back(shared->makeId(value));
            }
            eventSubscriptions.insert(std::make_pair(type, subscription));
        }
    }
}

bool frts::SidebarDrawer::updateEvents(SharedManagerPtr shared, bool forceUpdate)
{
    assert(initialized);
    assert(shared != nullptr);

    // Only update if necessary.
    if (!forceUpdate)
    {
        auto currentTime = shared->getFrame()->getRunTime();
        if (currentTime < eventsNextUpdate)
        {
            return false;
        }
        eventsNextUpdate += eventsUpdateTime;

        if (!eventsChanged)
        {
            return false;
        }
    }
    eventsChanged = false;

    PerformanceLog pl(getName() + " UpdateEvents", shared);

    // Limit number of events. Don't try to show more than possible. And remove an extra one for the
    // headline.
    auto fontHeight = TTF_FontHeight(font.get());
    while (events.size() * fontHeight > eventsHeight)
    {
        events.pop_back();
    }

    // Combine events to a long string.
    std::string text;
    for (auto& event : events)
    {
        auto it = eventSubscriptions.find(event->getType());
        if (it == eventSubscriptions.end())
        {
            continue;
        }
        auto subscription = it->second;
        auto eventText = boost::format(subscription.text);
        for (auto& valueId : subscription.eventValues)
        {
            auto eventValue = event->getValue(valueId);
            if (eventValue->getType() == eventValueFloat)
            {
                eventText = eventText % std::static_pointer_cast<FloatEventValue>(eventValue)->getValue();
            }
            if (eventValue->getType() == eventValueInteger)
            {
                eventText = eventText % std::static_pointer_cast<IntegerEventValue>(eventValue)->getValue();
            }
            if (eventValue->getType() == eventValueString)
             {
                 eventText = eventText % std::static_pointer_cast<StringEventValue>(eventValue)->getValue();
             }
            else if (eventValue->getType() == eventValueId)
            {
                eventText = eventText % std::static_pointer_cast<IdEventValue>(eventValue)->getValue();
            }
            else if (eventValue->getType() == eventValuePoint)
            {
                auto pos = std::static_pointer_cast<PointEventValue>(eventValue)->getValue();
                eventText = eventText % pos->getX();
                eventText = eventText % pos->getY();
                eventText = eventText % pos->getZ();
            }
            else
            {
                auto msg = boost::format(R"(Unsupported event value "%1%" with type "%2%".)")
                        % valueId % eventValue->getType();
                shared->getLog()->warning(getName(), msg.str());
            }
        }

        text += eventText.str();
        text += "\n";
    }
    if (text.empty())
    {
        return false;
    }

    // Calculate size.
    auto gd = getDataValue<GraphicData>(shared, Sdl2Ids::graphicData());
    auto area = gd->getSidebarArea();
    int maxWidth = area.width - 2 * padding;
    int maxHeight = eventsHeight - (eventsHeight % fontHeight);
    auto x = area.x + padding;
    auto y = area.y + eventOffset + padding;

    // Render and draw texture.
    auto texture = drawText(text, x, y, maxWidth, maxHeight, shared);
    bool ok = (texture != nullptr);
    if (ok)
    {
        eventTexture = texture;
    }

    return ok;
}

bool frts::SidebarDrawer::updateInfo(SharedManagerPtr shared, bool forceUpdate)
{
    assert(initialized);
    assert(shared != nullptr);

    // Only update if necessary.
    if (!forceUpdate)
    {
        auto currentTime = shared->getFrame()->getRunTime();
        if (currentTime < infoNextUpdate)
        {
            return false;
        }
        infoNextUpdate += infoUpdateTime;
    }

    PerformanceLog pl(getName() + " UpdateInfo", shared);

    // Get current cursor position.
    auto rm = getDataValue<RegionManager>(shared, ModelIds::regionManager());
    auto gd = getDataValue<GraphicData>(shared, Sdl2Ids::graphicData());
    auto cursor = gd->getCursor();
    auto pos = rm->getPos(cursor, shared);
    if (pos == nullptr)
    {
        return false;
    }

    // Find entity to show at position.
    auto renderableId = shared->makeId(Sdl2Ids::renderable());
    auto block = rm->getBlock(pos, shared);
    auto unfilteredEntities = block->getByComponent(renderableId);
    auto entities = unfilteredEntities;
    auto infoId = shared->makeId(ComponentIds::info());
    if (infoOnlyWithComponent)
    {
        entities.clear();
        for (auto& entity : unfilteredEntities)
        {
            if (entity->hasComponent(infoId))
            {
                entities.push_back(entity);
            }
        }
    }
    if (entities.empty())
    {
        return false;
    }

    // Show the last entity which is not the cursor. Nobody likes the cursor.
    auto entityToShow = entities.at(entities.size() - 1);
    if (entityToShow == cursor)
    {
        if (entities.size() >= 2)
        {
            entityToShow = entities.at(entities.size() - 2);
        }
        else
        {
            return false;
        }
    }
    if (entityToShow == infoLastEntity)
    {
        return false;
    }
    infoLastEntity = entityToShow;
    std::vector<EntityPtr> infoEntity = {entityToShow};

    // Calculate position of portrait and background.
    auto area = gd->getSidebarArea();
    int width = static_cast<int>(gd->getTileWidth() * tileZoom);
    int height = static_cast<int>(gd->getTileHeight() * tileZoom);
    auto backgroundWidth = width + 2 * padding;
    auto backgroundHeight = height + 2 * padding;
    int x = static_cast<int>(area.x + (area.width / 2) - (backgroundWidth / 2));
    int y = static_cast<int>(area.y + infoOffset + padding);

    SDL_Rect rectToRender = {
        static_cast<int>(x + padding),
        static_cast<int>(y + padding),
        width,
        height
    };

    // Draw background.
    drawRectangle(x, y, backgroundWidth, backgroundHeight,
                  tileBackgroundR, tileBackgroundG, tileBackgroundB);

    // Draw entity.
    drawer->renderEntities(infoEntity, renderableId, rectToRender, shared);

    // Entity info.
    auto msg = boost::format(infoText) % pos->getX() % pos->getY() % pos->getZ();
    std::string text = msg.str();
    if (entityToShow->hasComponent(infoId))
    {
        auto info = getComponent<Info>(infoId, entityToShow);
        auto information = info->getInformation();
        for (auto& infoItem : information)
        {
            text += "\n";
            text += infoItem.first->toString();
            text += ": ";
            text += infoItem.second->toString();
        }
    }

    // Render info.
    auto fontHeight = TTF_FontHeight(font.get());
    int maxWidth = area.width - 2 * padding;
    int maxHeight = infoTextHeight - (infoTextHeight % fontHeight);
    x = area.x + padding;
    y = y + backgroundHeight + padding;
    auto texture = drawText(text, x, y, maxWidth, maxHeight, shared);
    if (texture != nullptr)
    {
        infoTexture = texture;
    }

    // Draw separation line below info.
    auto separationY = y + maxHeight + padding;
    drawSeparationLine(area.x + padding, area.x + area.width - padding, separationY);

    eventOffset = separationY + 1; // + 1 because of line height.
    return true;
}

bool frts::SidebarDrawer::updateSidebar(SharedManagerPtr shared)
{
    assert(initialized);
    assert(shared != nullptr);

    PerformanceLog pl(getName() + " UpdateSidebar", shared);

    auto gd = getDataValue<GraphicData>(shared, Sdl2Ids::graphicData());
    auto area = gd->getSidebarArea();

    // Draw background.
    drawRectangle(area.x, area.y, area.width, area.height, backgroundR, backgroundG, backgroundB);

    // Draw info.
    bool result = updateInfo(shared, true);

    // Draw events.
    result = updateEvents(shared, true) || result;

    return result;
}

void frts::SidebarDrawer::validateData(SharedManagerPtr)
{
    if (eventsHeight == 0)
    {
        throw DataViolation("SidebarDrawer: Events height must be greater 0.");
    }

    if (fontPath.empty())
    {
        throw DataViolation("SidebarDrawer: Path to font not provided.");
    }

    if (fontSize <= 0)
    {
        throw DataViolation("SidebarDrawer: Font size must be greater 0.");
    }

    if (infoTextHeight == 0)
    {
        throw DataViolation("SidebarDrawer: Info text height must be greater 0.");
    }

    if (tileZoom == 0)
    {
        throw DataViolation("SidebarDrawer: Tile zoom must be greater 0.");
    }
}
