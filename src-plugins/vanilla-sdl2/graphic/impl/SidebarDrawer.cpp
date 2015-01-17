#include "SidebarDrawer.h"

#include <main/Sdl2Ids.h>

#include <frts/timer.h>

#include <boost/format.hpp>

#include <algorithm>


frts::SidebarDrawer::SidebarDrawer()
    : eventsNextUpdate{fromMilliseconds(0)}, eventsUpdateTime{fromMilliseconds(0)},
      infoNextUpdate{fromMilliseconds(0)}, infoUpdateTime{fromMilliseconds(0)}
{}

frts::SidebarDrawer::~SidebarDrawer()
{}

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
    SDL_RenderDrawLine(drawer->getRenderer().get(), static_cast<int>(startX), static_cast<int>(y),
                                                    static_cast<int>(endX), static_cast<int>(y));
}

frts::Drawer::TexturePtr frts::SidebarDrawer::drawText(const std::string& text,
                                                       GraphicData::pixel x, GraphicData::pixel y,
                                                       GraphicData::pixel maxWidth, GraphicData::pixel maxHeight,
                                                       const SharedManagerPtr& shared)
{
    Drawer::TexturePtr texture = nullptr;

    SDL_Surface* surface = TTF_RenderText_Blended_Wrapped(font.get(), text.c_str(), fontColor,maxWidth);
    if(surface == nullptr)
    {
        auto msg = boost::format(R"(TTF_RenderText_Blended_Wrapped Error: %1%)") % TTF_GetError();
        shared->getLog()->error(getName(), msg.str());
        return texture;
    }

    auto width = surface->w;

    auto fontHeight = TTF_FontHeight(font.get());
    auto height = (surface->h / fontHeight) * fontHeight;
    while (height > static_cast<int>(maxHeight))
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
        static_cast<int>(x),
        static_cast<int>(y),
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

void frts::SidebarDrawer::init(const DrawerPtr& drawer, const SharedManagerPtr& shared)
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

void frts::SidebarDrawer::notify(const EventPtr& event, const SharedManagerPtr&)
{
    assert(event != nullptr);

    events.push_front(event);
    eventsChanged = true;
}

void frts::SidebarDrawer::setSidebarConfig(const SharedManagerPtr& shared, const ConfigNodePtr& sidebarNode)
{
    assert(shared != nullptr);
    assert(sidebarNode != nullptr);

    auto md = getDataValue<MainData>(shared, MainIds::mainData());

    if (sidebarNode->has("background"))
    {
        auto rgbNode = sidebarNode->getNode("background");
        backgroundR = getCastInteger<std::uint8_t>(rgbNode, "r", backgroundR);
        backgroundG = getCastInteger<std::uint8_t>(rgbNode, "g", backgroundG);
        backgroundB = getCastInteger<std::uint8_t>(rgbNode, "b", backgroundB);
    }

    eventsHeight = getCastInteger<unsigned int>(sidebarNode, "events-height", eventsHeight);

    if (sidebarNode->has("events-update"))
    {
        eventsUpdateTime = fromMilliseconds(getCastInteger<unsigned int>(sidebarNode, "events-update"));
    }

    if (sidebarNode->has("font-color"))
    {
        auto rgbNode = sidebarNode->getNode("font-color");
        fontColor.r = getCastInteger<std::uint8_t>(rgbNode, "r", fontColor.r);
        fontColor.g = getCastInteger<std::uint8_t>(rgbNode, "g", fontColor.g);
        fontColor.b = getCastInteger<std::uint8_t>(rgbNode, "b", fontColor.b);
    }

    if (sidebarNode->has("font-path"))
    {
        fontPath = md->getPluginPath() + sidebarNode->getString("font-path");
    }

    fontSize = sidebarNode->getInteger("font-size", fontSize);

    infoOnlyWithComponent = sidebarNode->getBool("info-only-with-component", infoOnlyWithComponent);

    infoText = sidebarNode->getString("info-text", infoText);

    infoTextHeight = getCastInteger<unsigned int>(sidebarNode, "info-text-height", infoTextHeight);

    if (sidebarNode->has("info-update"))
    {
        infoUpdateTime = fromMilliseconds(getCastInteger<unsigned int>(sidebarNode, "info-update"));
    }

    if (sidebarNode->has("line-color"))
    {
        auto rgbNode = sidebarNode->getNode("line-color");
        lineColorR = getCastInteger<std::uint8_t>(rgbNode, "r", lineColorR);
        lineColorG = getCastInteger<std::uint8_t>(rgbNode, "g", lineColorG);
        lineColorB = getCastInteger<std::uint8_t>(rgbNode, "b", lineColorB);
    }

    padding = getCastInteger<unsigned int>(sidebarNode, "padding", padding);

    if (sidebarNode->has("tile-background"))
    {
        auto rgbNode = sidebarNode->getNode("tile-background");
        tileBackgroundR = getCastInteger<std::uint8_t>(rgbNode, "r", tileBackgroundR);
        tileBackgroundG = getCastInteger<std::uint8_t>(rgbNode, "g", tileBackgroundG);
        tileBackgroundB = getCastInteger<std::uint8_t>(rgbNode, "b", tileBackgroundB);
    }

    tileZoom = getCastInteger<unsigned int>(sidebarNode, "tile-zoom", tileZoom);

    if (sidebarNode->has("events"))
    {
        auto eventsNode = sidebarNode->getNode("events");
        for (auto node : *eventsNode)
        {
            auto type = shared->makeId(node->getString("type"));
            EventSubscription subscription;
            subscription.text = node->getString("text");
            if (node->has("values"))
            {
                for(auto& value : node->getStrings("values"))
                {
                    subscription.eventValues.push_back(shared->makeId(value));
                }
            }
            eventSubscriptions.insert(std::make_pair(type, subscription));
        }
    }
}

bool frts::SidebarDrawer::updateEvents(const SharedManagerPtr& shared, bool forceUpdate)
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

    PerformanceLog pl(getName() + " UpdateEvents", shared, 2);

    // Limit number of events. Don't try to show more than possible. And remove an extra one for the
    // headline.
    auto fontHeight = static_cast<GraphicData::pixel>(TTF_FontHeight(font.get()));
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
                        % valueId->toString() % eventValue->getType()->toString();
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
    auto maxWidth = area.width - 2 * padding;
    auto maxHeight = eventsHeight - (eventsHeight % fontHeight);
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

bool frts::SidebarDrawer::updateInfo(const SharedManagerPtr& shared, bool forceUpdate)
{
    assert(initialized);
    assert(shared != nullptr);

    // This function uses a couple of heuristics to detect if a update really is necessary.

    auto gd = getDataValue<GraphicData>(shared, Sdl2Ids::graphicData());

    // Only update if necessary.
    if (!forceUpdate && infoLastEntityIndex == gd->getSidebarInfoIndex())
    {
        auto currentTime = shared->getFrame()->getRunTime();
        if (currentTime < infoNextUpdate)
        {
            return false;
        }
        infoNextUpdate += infoUpdateTime;
    }
    infoLastEntityIndex = gd->getSidebarInfoIndex();

    PerformanceLog pl(getName() + " UpdateInfo", shared, 2);

    auto rm = getDataValue<RegionManager>(shared, ModelIds::regionManager());

    // Get current cursor position.
    auto pos = rm->getPos(gd->getCursor(), shared);
    if (pos == nullptr)
    {
        return false;
    }
    if (pos != infoLastPos)
    {
        gd->setSidebarInfoIndex(gd->sidebarInfoIndexDefault);
    }
    infoLastPos = pos;

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
    if (infoLastCountEntities != entities.size())
    {
        gd->setSidebarInfoIndex(gd->sidebarInfoIndexDefault);
    }
    infoLastCountEntities = entities.size();

    // Show the last entity.
    if (gd->getSidebarInfoIndex() == gd->sidebarInfoIndexDefault)
    {
        gd->setSidebarInfoIndex(std::max(0, static_cast<int>(entities.size()) - 1));
    }
    else
    {
        gd->setSidebarInfoIndex(gd->getSidebarInfoIndex() % static_cast<int>(entities.size()));
    }
    auto entityToShow = entities.at(static_cast<unsigned int>(gd->getSidebarInfoIndex()));
    if (!forceUpdate && entityToShow == infoLastEntity)
    {
        return false;
    }
    infoLastEntity = entityToShow;
    infoLastEntityIndex = gd->getSidebarInfoIndex(); // Save last index again because it may have changed.
    EntityVector infoEntity = {entityToShow};

    // Calculate position of portrait and background.
    auto area = gd->getSidebarArea();
    auto width = gd->getTileWidth() * tileZoom;
    auto height = gd->getTileHeight() * tileZoom;
    auto backgroundWidth = width + 2 * padding;
    auto backgroundHeight = height + 2 * padding;
    auto x = area.x + (area.width / 2) - (backgroundWidth / 2);
    auto y = area.y + infoOffset + padding;

    SDL_Rect rectToRender = {
        static_cast<int>(x + padding),
        static_cast<int>(y + padding),
        static_cast<int>(width),
        static_cast<int>(height)
    };

    // Draw background.
    drawRectangle(x, y, backgroundWidth, backgroundHeight,
                  tileBackgroundR, tileBackgroundG, tileBackgroundB);

    // Draw entity.
    IdUnorderedSet stacked;
    drawer->renderEntities(infoEntity, renderableId, rectToRender, stacked, shared, 1.0);

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
    auto fontHeight = static_cast<GraphicData::pixel>(TTF_FontHeight(font.get()));
    auto maxWidth = area.width - 2 * padding;
    auto maxHeight = infoTextHeight - (infoTextHeight % fontHeight);
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

bool frts::SidebarDrawer::updateSidebar(const SharedManagerPtr& shared)
{
    assert(initialized);
    assert(shared != nullptr);

    PerformanceLog pl(getName() + " UpdateSidebar", shared, 3);

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

void frts::SidebarDrawer::validateData(const SharedManagerPtr&)
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
