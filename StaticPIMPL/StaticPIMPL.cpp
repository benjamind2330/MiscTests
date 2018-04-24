// StaticPIMPL.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

#include "RSBuilder.hpp"



int main()
{
    RSMotion motionBuilder;
    motionBuilder.setRobot(5);
    
    std::cout << motionBuilder.getRobot() << std::endl;

    return 0;
}

