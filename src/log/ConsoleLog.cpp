#include "ConsoleLog.h"

#include <boost/format.hpp>

#include <ostream>


frts::ConsoleLog::ConsoleLog()
{
}

void frts::ConsoleLog::debug(const std::string& module, const std::string& msg)
{
    print("Debug", module, msg);
}

void frts::ConsoleLog::error(const std::string& module, const std::string& msg)
{
    print("Error", module, msg);
}

void frts::ConsoleLog::print(const std::string& level, const std::string& module,
                  const std::string& msg)
{
    std::string tmpl = R"(%1%: %2% - %3%)";
    auto formatted = boost::format(tmpl) % level % module % msg;
    std::cout << formatted.str() << std::endl;
}

void frts::ConsoleLog::info(const std::string& module, const std::string& msg)
{
    print("Info", module, msg);
}

void frts::ConsoleLog::warning(const std::string& module, const std::string& msg)
{
    print("Warning", module, msg);
}
