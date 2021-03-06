#pragma once


#include "GlobalTypes.hpp"

/// <summary>
/// Requirments of this file:
/// 1. Cannot see the interface.hpp file.
/// 2. Should use the file.
/// </summary>

struct MotionImpl;

class RSMotion
{
public:
    RSMotion();
    
    ~RSMotion();

    void setRobot(int robotId);
    int getRobot();

private:

    // Problems!
    // 1. Char array is not aligned the way that the type it is cast into will be.
    //    If we want to align, it is possible, but without knowing about the type we will have an issue. - Fixed
    // 2. Maintanence for changes in the motion will require changes here but they are not explicitly linked. - Fixed
    // 3. Need to be VERY VERY careful with default constructed operations like assignment and copy.  - Fixed
    //   (Probably means following rule of 3 in c++03, and rule of 5 otherwise (and maybe rule of 7 for windows))
    
    MotionImpl *ptr;
};

