
#include "ExampleModuleWithInput.h"
#include "ExampleConcreteRequiresConstruction.hpp"


using namespace evpc::hrm;


struct evpc::hrm::ConcreteItemsHolder
{
    ConcreteItemsHolder(evpc::fre::IExampleInterface &uses) :
        _concreteImpl(new ExampleConcreteRequiresIn(uses))
    { }

    boost::scoped_ptr<ExampleConcreteRequiresIn> _concreteImpl;
};


Module::Module(evpc::fre::IExampleInterface &otherObject) :
    _concrete(new ConcreteItemsHolder(otherObject)),
    _interface(*(_concrete->_concreteImpl))
{

}

Module::~Module() { }

