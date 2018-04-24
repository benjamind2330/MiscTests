#pragma once

template <class TBufferType>
class BinaryArchive
{
public:
    
    BinaryArchive(TBufferType &ioBuffer) :
        _buffer(ioBuffer)
    { }

    BinaryArchive(const BinaryArchive& copy) :
        _buffer(copy._buffer)
    { }

    template<typename T> bool push(const T& t)
    {
        const size_t size = sizeof(T);
        const char *data = reinterpret_cast<const char*>(&t);
        if (_buffer.getAvailableSize() < size) {
            return false;
        }
        size_t bytesWritten = _buffer.write(data, size);
        return bytesWritten == size;
    }

    template<typename T> bool pop(T& t)
    {
        const size_t size = sizeof(T);
        char *out = reinterpret_cast<char*>(&t);
        size_t bytesRead = _buffer.read(out, size);
        return bytesRead == size;
    }

    template<typename T> bool push(const T* t, size_t number)
    {

        size_t sizeToPush = sizeof(size_t) + number * sizeof(T);
        if (_buffer.getAvailableSize() < sizeToPush) {
            return false;
        }

        // Push the index
        {
            const size_t size = sizeof(size_t);
            char *data = reinterpret_cast<char*>(&number);
            size_t bytesWritten = _buffer.write(data, size);
            if (bytesWritten != size) {
                return false;
            }
        }

        // Push the data
        for (size_t i = 0; i < number; ++i) {
            const size_t size = sizeof(T);
            const char *data = reinterpret_cast<const char*>(&t[i]);
            size_t bytesWritten = _buffer.write(data, size);
            if (bytesWritten != size) {
                return false;
            }
        }

        return true;
    }

    /// <summary>
    /// Pop an array of objects from the buffer.
    /// </summary>
    /// <param name="t">The array to read into.</param>
    /// <param name="number">
    /// [IN | OUT] Used as the max size of t when passed in, set with the read 
    /// number of array items as an output.
    /// </param>
    /// <returns>
    /// True if successful. False in any of the cases where:
    /// - There is nothing remaining in the buffer. 
    /// - The number of serialized elements is less than that provided by number
    /// - The buffer does not contain the number of elements listed, (usually caused
    /// by trying to read an array you didnt push, or an array you pushed where there 
    /// wasnt enough space and you didnt check the output)
    /// </returns>
    template<typename T> bool pop(T* t, size_t &number)
    {
        // Read the index
        size_t serializedElements = 0;
        {
            const size_t size = sizeof(size_t);
            char *data = reinterpret_cast<char*>(&serializedElements);
            size_t bytesRead = _buffer.read(data, size);
            if (bytesRead != size) {
                return false;
            }

            if (serializedElements > number) {
                // Seek back one, so that a second read with a bigger buffer can succeed
                _buffer.seek(_buffer.getReadPosition() - sizeof(size_t));
                return false;
            }
        }

        // Pop the data
        for (size_t i = 0; i < serializedElements; ++i) {
            const size_t size = sizeof(T);
            char *data = reinterpret_cast<char*>(&t[i]);
            size_t bytesRead = _buffer.read(data, size);
            if (bytesRead != size) {
                return false;
            }
        }

        number = serializedElements;

        return true;
    }

    inline void clear()
    {
        _buffer.clear();
    }

    inline bool isEmpty() const
    {
        return _buffer.isEmpty();
    }

    inline void resetReadPosition()
    {
        _buffer.seek(0);
    }

    /// <summary>
    /// Get the current used size of the buffer, not only the data but the metadatas.
    /// </summary>
    inline size_t getCurrentSize() const
    {
        return _buffer.getMaxSize() - _buffer.getAvailableSize();
    }

    bool peekNextElementAsArraySize(size_t &sizeOfArray)
    {
        const size_t size = sizeof(size_t);
        char *data = reinterpret_cast<char*>(&sizeOfArray);
        size_t bytesRead = _buffer.read(data, size);
        if (bytesRead != size) {
            return false;
        }

        // Seek back one, so that a second read can succeed
        _buffer.seek(_buffer.getReadPosition() - sizeof(size_t));
        return true;
    }

private:

    TBufferType &_buffer;
};
