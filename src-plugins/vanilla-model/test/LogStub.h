#ifndef LOGSTUB_H
#define LOGSTUB_H

#include <frts/log>


class TestLog : public frts::Log
{
public:
    TestLog() {}
    ~TestLog() {}
    void debug(const std::string&, const std::string&) override {}
    void error(const std::string&, const std::string&) override {}
    void info(const std::string&, const std::string&) override {}
    void warning(const std::string&, const std::string&) override {}
};

#endif // LOGSTUB_H
