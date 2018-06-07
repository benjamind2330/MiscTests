// TestStackString.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>

//#include <base/stack_container.h>
#include <xstring>



int main()
{

    //StackString<300> s;
    
    xstr::xstring<xstr::fixed_char_buf<64> >  small_string;
    small_string.find_first_not_of('l');

    return 0;
}

