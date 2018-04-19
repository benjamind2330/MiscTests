// IntializerWarningCheck.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


class test
{
public:
    test() :
        c(5),
        b(c),
        a(b)
    { }

private:
    int a;
    int &b, c;
};


int main()
{

    test t;
    return 0;
}

