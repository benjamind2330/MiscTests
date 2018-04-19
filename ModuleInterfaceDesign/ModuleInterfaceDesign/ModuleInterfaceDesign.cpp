// ModuleInterfaceDesign.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "ExampleModule.hpp"
#include "ExampleModuleWithInput.h"

class Controller
{
public:

    Controller() :
        hrmModule(freModule._exampleInterface)
    { }

    evpc::fre::Module freModule;
    evpc::hrm::Module hrmModule;
};


int main()
{

    Controller controller;

    controller.freModule._exampleInterface.exampleFunction();
    controller.hrmModule._interface.exampleFunction();


    while (true);

    return 0;
}

