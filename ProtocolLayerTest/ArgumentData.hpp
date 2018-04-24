#pragma once

#include "SimpleBuffer.hpp"
#include "BinaryArchive.hpp"


class ArgumentData
{
public:
    ArgumentData() :
        command(-1)
    { }

    int getcommand() const
    {
        return command;
    }

    void setCommand(int s)
    {
        command = s;
    }

    bool serialize(SimpleBuffer &buffer)
    {
        BinaryArchive<SimpleBuffer> ar(buffer);
        return ar.push(command);
    }

    size_t dataSize() const
    {
        return sizeof(command);
    }

    bool deserialize(SimpleBuffer &buffer)
    {
        BinaryArchive<SimpleBuffer> ar(buffer);
        return ar.pop(command);
    }
    
private:

    int command;

};




