#pragma once

#include "SimpleBuffer.hpp"
#include "BinaryArchive.hpp"


class RoutineLayerData
{
public:
    RoutineLayerData()
    {}

    RoutineLayerData(int a, char b) :
        data1(a),
        data2(b) 
    {}

    inline int get1() const { return data1; }
    inline char get2() const { return data2; }

    bool serialize(SimpleBuffer &buffer)
    {
        BinaryArchive<SimpleBuffer> ar(buffer);
        return ar.push(data1) && ar.push(data2);
    }

    size_t dataSize() const
    {
        return sizeof(data1) + sizeof(data2);
    }

    bool deserialize(SimpleBuffer &buffer)
    {
        BinaryArchive<SimpleBuffer> ar(buffer);
        return ar.pop(data1) && ar.pop(data2);
    }

private:

    int data1;
    char data2;

};