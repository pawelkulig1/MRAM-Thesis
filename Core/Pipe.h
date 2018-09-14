#pragma once

#include <fstream>
#include <iostream>

enum STATE {
    READ,
    WRITE,
    IDLE,
    CLOSED,
};

class Pipe
{
private:
    bool open();
    bool close();
    STATE state;    
    std::string pipeName;
    std::fstream pipeHandle;

public:
    Pipe();
    Pipe(std::string name);
    ~Pipe();
    bool create(std::string);
    bool checkIfExists(std::string filename);
    bool write(std::string data);
    std::string read();
};
