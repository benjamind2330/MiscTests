#pragma once


#include "GlobalTypes.hpp"

/// <summary>
/// Requirments of this file:
/// 1. Cannot see the interface.hpp file.
/// 2. Should use the file.
/// </summary>

class RSMotion
{
public:
    RSMotion();
    
    ~RSMotion();

    void setRobot(int robotId);
    int getRobot() const;

    const static size_t SIZE_OF_IMPLEMENTATION = sizeof(int) * 2;

private:

    // Problems!
    // 1. Char array is not aligned the way that the type it is cast into will be.
    // 2. Maintanence for chaanges in the motion will require changes here but they are not explicitly linked.
    // 3. Need to be VERY VERY careful with default constructed operations like assignment and copy. 
    //   (Probably means following rule of 3 in c++03, and rule of 5 otherwise (and maybe rule of 7 for windows))
    
    void *_internalMotion;
    char _typeMem[SIZE_OF_IMPLEMENTATION];
    
};

