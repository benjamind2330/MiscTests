#pragma once


// ====================================================================================
// In general header file.
template<typename SerialPortType>
class SerialPortTemplate
{
public:

    int open(int port)
    {
        return static_cast<SerialPortType*>(this)->openImpl(port);
    }


    int close()
    {
        return static_cast<SerialPortType*>(this)->closeImpl();
    }
};

#include "Child.h"
class OSSpecificSerialPort;
typedef SerialPortTemplate<OSSpecificSerialPort> SerialPort;
