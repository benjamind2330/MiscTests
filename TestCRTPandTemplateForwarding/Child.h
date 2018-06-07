#pragma once

#include "Header.h"

// ====================================================================================
// In os specific file
class OSSpecificSerialPort : public SerialPortTemplate<OSSpecificSerialPort>
{
public:

    int openImpl(int port);


    int closeImpl();
private:
    int _port;
};


