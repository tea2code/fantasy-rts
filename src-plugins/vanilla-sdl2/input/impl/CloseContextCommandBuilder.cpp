#include "CloseContextCommandBuilder.h"

#include "CloseContextCommand.h"


frts::CloseContextCommandBuilder::CloseContextCommandBuilder(const IdPtr& commandType, bool resetToDefault)
    : commandType{commandType}, resetToDefault{resetToDefault}
{

}

frts::CloseContextCommandBuilder::~CloseContextCommandBuilder()
{

}

frts::CommandPtr frts::CloseContextCommandBuilder::build(const SharedManagerPtr&)
{
    return makeCloseContextCommand(commandType, resetToDefault);
}
