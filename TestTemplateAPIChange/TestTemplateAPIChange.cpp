// TestTemplateAPIChange.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <type_traits>

enum Type { T1, T2, T3 };

template <Type TType> struct VarApi {
    void common() { }

    template <Type T = TType,
        typename = typename std::enable_if<T == T1 && T == TType>::type
    >
    void funcA1() { }

    template <Type T = TType,
        typename = typename std::enable_if<T == T2 && T == TType>::type
    >
    void funcA2() { }

    template <Type T = TType,
        typename = typename std::enable_if<(T == T1 || T == T2) && T == TType>::type 
    >
        void funcA1_2() { }

    template <Type T = TType,
        typename = typename std::enable_if<T == T3 && T == TType>::type
    >
        void funcA3() { }
};


/*
template<Type T, class Derived> struct func_provider;

template<class Derived>
struct func_provider<Type::T1, Derived> { void funcA1() { } };

template<class Derived> struct func_provider<Type::T2, Derived> { void funcA2() { } };

template<Type T>
struct foo : public func_provider<T, foo<T>> { 
    void common()
    {
        auto self = static_cast<Derived*>(this);

        // do something with self
    }
};
*/

int main()
{
    VarApi<T1> v1;
    v1.common();
    v1.funcA1();
    // v1.funcA2(); // ERROR
    v1.funcA1_2();
    
    VarApi<T2> v2;
    v1.common();
    // v2.funcA1(); // ERROR
    v2.funcA2();
    v1.funcA1_2();

   // v2.funcA1<T1>(); // NOT ERROR

    /*
    foo<T1> f1;
    foo<T2> f2;
    f1.common();
    f1.funcA1();
    // f.funcA2(); // Error
    f2.common();
    f2.funcA2();
    // g.funcA1(); // Error
    */
    return 0;
}

