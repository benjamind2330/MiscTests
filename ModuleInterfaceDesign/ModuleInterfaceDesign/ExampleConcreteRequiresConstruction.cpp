#include "ExampleConcreteRequiresConstruction.hpp"

using namespace evpc::hrm;

ExampleConcreteRequiresIn::ExampleConcreteRequiresIn(evpc::fre::IExampleInterface &uses)
    : _uses(uses)
{
}


int ExampleConcreteRequiresIn::exampleFunction()
{
    return _uses.exampleFunction() + 1;
}
