#pragma once

namespace evpc {
namespace fre {

static const int someInt = 5;

class IExampleInterface
{
public:
    virtual int exampleFunction() = 0;
};

class IExampleInterface2
{
public:
    virtual int exampleFunction2() = 0;
};


}


namespace hrm {

class IExampleInterface
{
public:
    virtual int exampleFunction() = 0;
};


}

}