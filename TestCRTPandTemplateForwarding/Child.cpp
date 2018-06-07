#include "Child.h"

int OSSpecificSerialPort::openImpl(int port)
{
    return _port = port;
}


int OSSpecificSerialPort::closeImpl()
{
    return _port = 0;
}