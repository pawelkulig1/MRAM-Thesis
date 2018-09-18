#pragma once
#include <string>
#include <fstream>

namespace Parser
{
    class ParserInterface
    {
    private:
        std::string filename;
        std::string configName;
        sdt::fstream fileHandle;
    public:
        virtual void parseData() = 0;
        virtual void parseConfig() = 0;
    };
}
