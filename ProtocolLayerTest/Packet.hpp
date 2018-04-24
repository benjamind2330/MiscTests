#pragma once



#include <functional>

#include "SimpleBuffer.hpp"

class Packet
{
public:
    Packet(size_t size) :
        _buffer(size)
    { }

    bool addLayer(std::function<bool(SimpleBuffer&)> serializeFunction, std::function<size_t(void)> sizeFunction)
    {
        if (_buffer.getAvailableSize() < sizeFunction()) {
            return false;
        }
        return serializeFunction(_buffer);
    }

    bool popLayer(std::function<bool(SimpleBuffer&)> deserializeFunction)
    {
        return deserializeFunction(_buffer);
    }

    size_t write(char *output, size_t maxSize) const
    {
        if (maxSize < _buffer.size()) {
            return 0;
        }
        std::memcpy(output, _buffer(), _buffer.size());
        return _buffer.size();
    }


    size_t read(const char* input, size_t size)
    {
        if (size > _buffer.getMaxSize()) {
            return 0;
        }
        return _buffer.write(input, size);
    }

   
private:

    SimpleBuffer _buffer;

};
