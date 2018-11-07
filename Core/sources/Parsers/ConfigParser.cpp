#include "ConfigParser.h"

ConfigParser::ConfigParser(std::string configFilename): configFilename(configFilename)
{
    read_json(this->configFilename, pt);
}
