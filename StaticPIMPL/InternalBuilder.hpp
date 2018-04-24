#pragma once

#include "GlobalTypes.hpp"





class InternalBuilder
{
public:

    InternalBuilder() { }
    types::Motion::Type motionType;
    int robotId;

};

namespace constants {
const size_t RSBuilderSize = sizeof(InternalBuilder);
}






