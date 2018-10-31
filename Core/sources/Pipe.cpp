#include "Pipe.h"

Pipe::Pipe()
{
    state = CLOSED;    
}

Pipe::Pipe(std::string name): pipeName(name)
{
    state = CLOSED;
}

Pipe::~Pipe()
{
    write(";|;|;|");
    state = CLOSED;
}

bool Pipe::create(std::string)
{
    //TODO       
    return 1;
}

bool Pipe::checkIfExists(std::string filename)
{
    std::fstream tempHandle;
    tempHandle.open(filename, std::ios::out | std::ios::in);
    bool status = tempHandle.good();
    tempHandle.close();
    return status;
}

bool Pipe::write(std::string data)
{
    state = WRITE;
    pipeHandle.open(pipeName, std::ios::out);
    if(!pipeHandle.good())
        return false;
    pipeHandle << data;
    pipeHandle.close();
    state = IDLE;
    return true;
}

std::string Pipe::read()
{
    state = READ;
    pipeHandle.open(pipeName, std::ios::in);
    if(!pipeHandle.good())
        throw("Unable to open Pipe: " + pipeName + " !");

    std::string data;
    pipeHandle >> data;

    state = IDLE;
    return data;
}
