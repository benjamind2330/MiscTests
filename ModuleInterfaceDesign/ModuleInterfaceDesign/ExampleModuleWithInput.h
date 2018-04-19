#pragma once

#include "ExampleInterface.hpp"
#include <boost/scoped_ptr.hpp>

namespace evpc {
namespace hrm {

struct ConcreteItemsHolder;

struct Module
{
private:
    boost::scoped_ptr<ConcreteItemsHolder> _concrete;

public:
    Module(evpc::fre::IExampleInterface &otherObject);
    ~Module();
    evpc::hrm::IExampleInterface &_interface;
};


}
}



