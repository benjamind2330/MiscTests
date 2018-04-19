#pragma once

#include "ExampleInterface.hpp"
#include <boost/scoped_ptr.hpp>


namespace evpc {
namespace fre {

struct ConcreteItemsHolder;

struct Module
{
private:
        
    boost::scoped_ptr<ConcreteItemsHolder> _concrete;

public:
    Module();
    ~Module();
    IExampleInterface &_exampleInterface;
    IExampleInterface2 &_exampleInterface2;

};
}
}



