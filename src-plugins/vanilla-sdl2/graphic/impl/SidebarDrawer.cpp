#include "SidebarDrawer.h"

#include <main/Sdl2Ids.h>
#include <frts/shared>

#include <boost/format.hpp>


frts::SidebarDrawer::SidebarDrawer()
    : eventsNextUpdate{fromMilliseconds(0)}, eventsUpdateTime{fromMilliseconds(0)}
{}

frts::SidebarDrawer::~SidebarDrawer()
{
    texture.reset();
    renderer.reset();
}

void frts::SidebarDrawer::drawRectangle(GraphicData::Pixel x, GraphicData::Pixel y, GraphicData::Pixel width, GraphicData::Pixel height,
                                        std::uint8_t r, std::uint8_t g, std::uint8_t b)
{
    SDL_Rect rectToRender = {
        static_cast<int>(x),
        static_cast<int>(y),
        static_cast<int>(width),
        static_cast<int>(height)
    };
    SDL_SetRenderDrawColor(renderer.get(), r, g, b, 0);
    SDL_RenderFillRect(renderer.get(), &rectToRender);
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

void frts::SidebarDrawer::init(Drawer::RendererPtr renderer, SharedManagerPtr shared)
{
    assert(renderer != nullptr);
    assert(shared != nullptr);

    // Set renderer.
    this->renderer = renderer;

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

    auto gd = getDataValue<GraphicData>(shared, Sdl2Ids::graphicData());
    auto area = gd->getSidebarArea();

    // Create texture and calculate size.
    int width = area.width - 2 * padding;

    SDL_Surface* surface = TTF_RenderText_Blended_Wrapped(font.get(), text.c_str(), fontColor, width);
    if(surface == nullptr)
    {
        auto msg = boost::format(R"(TTF_RenderText_Blended_Wrapped Error: %1%)") % TTF_GetError();
        shared->getLog()->error(getName(), msg.str());
        return false;
    }

    int height = (surface->h / fontHeight) * fontHeight;
    while (height > static_cast<int>(eventsHeight))
    {
        height -= fontHeight;
    }

    texture = std::shared_ptr<SDL_Texture>(
        SDL_CreateTextureFromSurface(renderer.get(), surface),
        Drawer::Sdl2Deleter()
    );
    SDL_FreeSurface(surface);
    if(texture == nullptr)
    {
        auto msg = boost::format(R"(SDL_CreateTextureFromSurface Error: %1%)") % SDL_GetError();
        shared->getLog()->error(getName(), msg.str());
        return false;
    }

    // Draw background.
    auto startX = area.x + padding;
    auto startY = area.y + padding;
    drawRectangle(startX, startY, width, height, backgroundR, backgroundG, backgroundB);

    // Draw text.
    SDL_Rect rectToRender = {
        static_cast<int>(startX),
        static_cast<int>(startY),
        width,
        height
    };
    SDL_Rect clip = {
        0,
        0,
        width,
        height
    };
    SDL_RenderCopy(renderer.get(), texture.get(), &clip, &rectToRender);

    return true;
}

bool frts::SidebarDrawer::updateInfo(SharedManagerPtr shared, bool)
{
    assert(initialized);
    assert(shared != nullptr);

    // TODO

    return false;
}

bool frts::SidebarDrawer::updateSidebar(SharedManagerPtr shared)
{
    assert(initialized);
    assert(shared != nullptr);

    auto gd = getDataValue<GraphicData>(shared, Sdl2Ids::graphicData());
    auto area = gd->getSidebarArea();

    // Draw background.
    drawRectangle(area.x, area.y, area.width, area.height, backgroundR, backgroundG, backgroundB);

    // Draw info.
    bool result = updateInfo(shared, true);

    // Draw events.
    result = result || updateEvents(shared, true);

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
}
