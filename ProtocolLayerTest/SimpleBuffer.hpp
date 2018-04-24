#pragma once

#include <utility>
#include <vector>

class SimpleBuffer
{
public:

    SimpleBuffer(size_t size) :
        _buffer(size),
        _readPosition(0),
        _writePosition(0)
    {

    }

    size_t getAvailableSize()
    {
        return _buffer.size() - _writePosition;
    }

    size_t getMaxSize()
    {
        return _buffer.size();
    }

    size_t write(const char *data, size_t size)
    {
        size_t writeCount = 0;
        while (size-- && _writePosition < _buffer.size()) {
            _buffer[_writePosition++] = data[writeCount++];
        }
        return writeCount;
    }

    size_t read(char* data, size_t maxSize)
    {
        size_t readCount = 0;
        while (maxSize-- && _readPosition < _writePosition) {
            data[readCount++] = _buffer[_readPosition++];
        }
        return readCount;
    }

    void clear()
    {
        _readPosition = _writePosition = 0;
    }

    bool isEmpty()
    {
        return _writePosition == 0;
    }

    bool seek(size_t position)
    {
        if (position > _writePosition) {
            return false;
        }
        return true;
    }

    size_t size() const
    {
        return _writePosition;
    }

    const char *operator()() const
    {
        return _buffer.data();
    }

    char *operator()()
    {
        return _buffer.data();
    }

private:

    size_t _readPosition;
    size_t _writePosition;
    std::vector<char> _buffer;
};