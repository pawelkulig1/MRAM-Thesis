#ifndef __PLAIN_DATA_PARSER_H__
#define __PLAIN_DATA_PARSER_H__
#include <iostream>
#include <fstream>
#include <deque>
#include <boost/algorithm/string.hpp> //split

#include "../Point.h"
using namespace GNEB;

namespace Parser
{
	class PlainDataParser
	{
		std::string filename;
		std::string confname;
		std::fstream handle;
		std::string tempData;
		int xsize, ysize;
		double dx, dy, xpos, ypos;
		bool parseConfig();
        void incrementer(int &poz1, int &poz2, std::string &temp);
    public:
		PlainDataParser(std::string filename);
		void parse(std::deque<std::deque<Point> > *p);
		int getXSize();
		int getYSize();
		double getXpos();
		double getYpos();
		double getDx();
		double getDy();
	};
}

#endif //__PLAIN_DATA_PARSER_H__
