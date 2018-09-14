#include "ChainSaver.h"

int ChainSaver::counter = 0;


ChainSaver::ChainSaver(string filename): filename(filename)
{
}

string ChainSaver::saveChain()
{
    filename = filename + to_string(counter);
    handle.open(filename, std::ios::app);
    if(!handle.good())
    {
        cout<<"cannot open file!"<<endl;
        throw("Cannot open file!");
    }
    counter++;

    string temp;
    Chain *c = Chain::getInstance();
    
    temp += PointToStr(c->getFirst());
    for(int i=0;i<c->size();i++)
    {
        temp += PointToStr(c->getPoint(i));
    }
    temp += PointToStr(c->getLast());

    handle.close();

}

string ChainSaver::PointToStr(Point *im)
{
    return to_string(im->getX()) +","+ to_string(im->getY()) +","+ to_string(im->getZ()) + ";";
}

string ChainSaver::PointToStr(Point im)
{

    return to_string(im.getX()) +","+ to_string(im.getY()) +","+ to_string(im.getZ()) + ";";
}
