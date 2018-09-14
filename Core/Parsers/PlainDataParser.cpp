#include "PlainDataParser.h"

using namespace Parser;

PlainDataParser::PlainDataParser(std::string filename): filename(filename)
{
	confname = filename.substr(0, filename.find(".dat")) + ".conf";
}

void PlainDataParser::incrementer(int &poz1, int &poz2, std::string &temp)
{	
	poz1 = poz2;
	poz2 = temp.find(",", poz1+1);
}

bool PlainDataParser::parseConfig()
{
    ysize = 0;
    xsize = 0;
    dx = 0;
    dy = 0;
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
	xsize = std::stoi(temp.substr(0, poz1));
	int poz2 = temp.find(",", poz1+1);
	ysize = std::stoi(temp.substr(poz1+1, poz2));
	incrementer(poz1, poz2, temp);
	dx = std::stod(temp.substr(poz1+1, poz2))/xsize;
	incrementer(poz1, poz2, temp);
	dy = std::stod(temp.substr(poz1+1, poz2))/ysize;
	incrementer(poz1, poz2, temp);
	xpos = std::stod(temp.substr(poz1+1, poz2));
	incrementer(poz1, poz2, temp);
	ypos = std::stod(temp.substr(poz1+1, poz2));

    if(!xsize || !ysize || !dx || !dy)
    {
        return false;
    }
    return true;

}

void PlainDataParser::parse(std::deque<std::deque<Point>> *data)
{
    if(!parseConfig())
    {
        std::cout<<"Config fille cannot be parsed!"<<std::endl;
        throw("Config fille cannot be parsed!");
    }
	handle.open(filename, std::ios::in);
	std::string temp;
	if(!handle.good())
	{
		std::cout<<"PlainDataParser::parse() Unable to open file"<<std::endl;
        throw("Unable to open file!");
	}

   	handle >> temp;
	handle.close();
		
	std::deque<std::string> lines;
	boost::split(lines, temp, boost::is_any_of(",")); 
	std::deque<Point > deqTemp;
	std::deque<std::string>::iterator it = lines.begin();
	for(int j=0;j<ysize;j++)
	{
		if(!deqTemp.empty())
            deqTemp.erase(deqTemp.begin(), deqTemp.end());	
		for(int i=0;i<xsize;i++)
		{
			Point p = Point(i*dx + xpos, j*dy + ypos, std::stod(*it));
			deqTemp.push_back(p);
			it++;
		}
	    data->push_back(deqTemp);
	}
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
