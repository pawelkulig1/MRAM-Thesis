#pragma once
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include <string.h>
#include <vector>
#include <iostream>

using namespace boost::property_tree;

class ConfigParser
{
    ptree pt;
    std::string configFilename;
public:
    ConfigParser(std::string configFilename);
    

    template <class T> T getValue(std::string path) 
    {
        return pt.get<T>(path);  
    };

    template <typename T> std::vector<T> getVector(ptree::key_type const& key)
    {
        std::vector<T> r;
        for (auto& item : pt.get_child(key))
            r.push_back(item.second.get_value<T>());
        return r;
    }

    template <typename T> std::vector<std::vector<T> > getMatrix(ptree::key_type const& key)
    {
        std::vector<std::vector<T> > vec;
        int y = 0;
        for (ptree::value_type &row : pt.get_child(key))
        {
            std::vector<T> temp;
            vec.push_back(temp);
            for (ptree::value_type &cell : row.second)
            {
                vec[y].push_back(cell.second.get_value<T>());
                //std::cout<<cell.second.get_value<T>() << std::endl;
            }
            y++;
        }
        return vec;
    }
};
