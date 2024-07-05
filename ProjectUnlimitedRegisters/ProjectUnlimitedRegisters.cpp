// ProjectUnlimitedRegisters.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "CommandList.h"
#include "Tests.h"

int main()
{
    runtests();
    CommandList c;
    c.run();

}