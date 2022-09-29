// SPDX-License-Identifier: MIT
//
// This file demonstrates the usage of the nullptr keyword in C++11.

// C standard library inclusions
#include <cstddef>  // for std::nullptr_t data type

// C++ standard library inclusions
#include <iostream> // General I/O operations

void PrintPointerAddress(int* p)
{
    std::cout << "Pointer to integer points to: " << std::hex << p << std::endl;
}

void PrintPointerAddress(double* p)
{
    std::cout << "Pointer to double points to: " << std::hex << p << std::endl;
}

void PrintPointerAddress(std::nullptr_t p)
{
    std::cout << "Null Pointer detected!" << std::endl;
}

// TODO: Can we be more generic and not overload every data type?

int main()
{
    int* a {};
    double* b {};

    PrintPointerAddress(a);
    PrintPointerAddress(b);
    PrintPointerAddress(nullptr);
    //PrintPointerAddress(0); // ERROR: call of overloaded ‘PrintPointerAddress(int)’ is ambiguous
    //PrintPointerAddress(NULL); // ERROR: call of overloaded ‘PrintPointerAddress(NULL)’ is ambiguous

    return 0;
}
