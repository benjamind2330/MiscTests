#include "ExampleConcrete.hpp"
#include "ExampleInterface.hpp"
#include "ExampleModule.hpp"

using namespace evpc::fre;

struct evpc::fre::ConcreteItemsHolder
{
    ConcreteItemsHolder() :
        _concreteImpl(new ExampleConcrete)
    { }

    boost::scoped_ptr<ExampleConcrete> _concreteImpl;
};


Module::Module() :
    _concrete(new ConcreteItemsHolder),
    _exampleInterface(*(_concrete->_concreteImpl)),
    _exampleInterface2(*(_concrete->_concreteImpl))
{ }

Module::~Module() { }