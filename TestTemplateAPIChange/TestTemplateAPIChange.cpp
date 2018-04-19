// TestTemplateAPIChange.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <type_traits>

enum Type { T1, T2, T3 };

template <Type TType> class VarApi {

public:
    template <Type T = TType,
        typename = typename std::enable_if<T == T1>::type>
    void funcA1()
    { }

    template <Type T = TType,
        typename = typename std::enable_if<T == T2>::type >
    void funcA2()
    { }

    template <Type T = TType,
        typename = typename std::enable_if<T == T1 || T == T2>::type >
        void funcA1_2()
    { }
};



int main()
{
    VarApi<T1> v1;
    v1.funcA1();
    // v1.funcA2(); // ERROR
    v1.funcA1_2();
    
    VarApi<T2> v2;
    // v2.funcA1(); // ERROR
    v2.funcA2();
    v1.funcA1_2();

    v2.funcA1<T1>(); // NOT ERROR

    return 0;
}

