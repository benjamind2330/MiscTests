#pragma once

#include "ExampleInterface.hpp"

namespace evpc {
namespace fre {

class ExampleConcrete : public IExampleInterface, public IExampleInterface2
{
public:
    virtual int exampleFunction();
    virtual int exampleFunction2();
};


}
}
