#pragma once
#include <string>
#include <fstream>

namespace Parser
{
    class DataParserInterface
    {
    private:
        std::string filename;
        std::string configName;
        std::fstream fileHandle;
    public:
        virtual void parseData() = 0;
        virtual void parseConfig() = 0;
    };
}
