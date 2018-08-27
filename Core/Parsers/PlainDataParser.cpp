#include "PlainDataParser.h"

using namespace Parser;

PlainDataParser::PlainDataParser(std::string filename): filename(filename)
{
	confname = filename.substr(0, filename.find(".dat")) + ".conf";
}

void inline incrementer(int &poz1, int &poz2, std::string &temp)
{	
	poz1 = poz2;
	poz2 = temp.find(",", poz1+1);
}

bool PlainDataParser::parseConfig()
{
	handle.open(confname, std::ios::in);
	if(!handle.good())
	{	
        std::cout<<"PlainDataParser::parseConfig() Unable to open file!"<<std::endl;
        return false;
	}

	std::string temp;
	handle >> temp;
	handle.close();
	int poz1 = temp.find(",");
	xsize = std::stoi(temp.substr(0, poz1), nullptr);
	int poz2 = temp.find(",", poz1+1);
	ysize = std::stoi(temp.substr(poz1+1, poz2), nullptr);
	incrementer(poz1, poz2, temp);
	dx = std::stoi(temp.substr(poz1+1, poz2), nullptr)/xsize;
	incrementer(poz1, poz2, temp);
	dy = std::stoi(temp.substr(poz1+1, poz2), nullptr)/ysize;
	incrementer(poz1, poz2, temp);
	xpos = std::stoi(temp.substr(poz1+1, poz2), nullptr);
	incrementer(poz1, poz2, temp);
	ypos = std::stoi(temp.substr(poz1+1, poz2), nullptr);
    return true;

}

std::deque<std::deque<Point *>> PlainDataParser::parse()
{
    std::deque<std::deque<Point *>> data;

    if(!parseConfig())
        return data; 
	handle.open(filename, std::ios::in);
	std::string temp;
	if(!handle.good())
	{
		std::cout<<"PlainDataParser::parse() Unable to open file"<<std::endl;
	}

   	handle >> temp;
	handle.close();
		
	std::deque<std::string> lines;
	boost::split(lines, temp, boost::is_any_of(",")); 
	std::deque<Point *> deqTemp;
	std::deque<std::string>::iterator it = lines.begin();
	for(int j=0;j<ysize;j++)
	{
		deqTemp.erase(deqTemp.begin(), deqTemp.end());	
		for(int i=0;i<xsize;i++)
		{
			Point *p = new Point(i*dx + xpos, j*dy + ypos, std::stod(*it, nullptr));
			deqTemp.push_back(p);
			it++;
		}
		data.push_back(deqTemp);
	}
	return data;
}

int PlainDataParser::getXSize()
{
	return xsize;
}

int PlainDataParser::getYSize()
{
	return ysize;
}

double PlainDataParser::getXpos()
{
	return xpos;
}

double PlainDataParser::getYpos()
{
	return ypos;
}

double PlainDataParser::getDx()
{
	return dx;
}

double PlainDataParser::getDy()
{
	return dy;
}
