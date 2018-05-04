#pragma once

#include "GlobalTypes.hpp"



class InternalBuilder
{
public:

    InternalBuilder() { }
    types::Motion::Type motionType;
    int robotId;
};


typedef InternalBuilder InternalImplementation;





