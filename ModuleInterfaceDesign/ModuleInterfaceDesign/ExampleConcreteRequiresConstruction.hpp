#pragma once

#include "ExampleInterface.hpp"

namespace evpc {
namespace hrm {

class ExampleConcreteRequiresIn : public IExampleInterface
{   
    evpc::fre::IExampleInterface &_uses;

public:

    ExampleConcreteRequiresIn(evpc::fre::IExampleInterface &uses);
    virtual int exampleFunction();
    
};


}
}