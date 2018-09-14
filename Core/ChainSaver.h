#pragma once

#include "Chain.h"
#include <string>
#include <iostream>

using namespace std;

class ChainSaver
{    
    static int counter;
    string filename;
    fstream handle;
public:
    ChainSaver(string filename);
    string saveChain();
    string PointToStr(Point *im);
    string PointToStr(Point im);


};

