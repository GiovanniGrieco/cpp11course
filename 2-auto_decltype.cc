// SPDX-License-Identifier: MIT
//
// This file demonstrates the usage of auto keyword available in C++11.

// C++ standard library inclusions
#include <iostream> // general I/O
#include <typeinfo> // utilities to retrieve data type information at runtime

#ifdef __GNUC__
#include <cxxabi.h> // GCC-specific utilities

// GCC-specific macro to demangle the data type name at runtime
#define GetTypeId(x) abi::__cxa_demangle(typeid(x).name(), 0, 0, nullptr)
#else // For any other compiler
#define GetTypeId(x) typeid(x).name()
#endif

// Here you can see how things may go out of hand if the syntax is too explicit
// and verbose.
void ExplicitSyntax()
{
    int a = int {42};
    short b = short {42};
    std::string c {"Hello world!"};
    int* d = new int[5] {1, 2, 3, 4, 5};

    std::cout << "=== Explicit Syntax ===" << std::endl;
    std::cout << "Type of a is: " << GetTypeId(a) << std::endl;
    std::cout << "Type of b is: " << GetTypeId(b) << std::endl;
    std::cout << "Type of c is: " << GetTypeId(c) << std::endl;
    std::cout << "Type of d is: " << GetTypeId(d) << std::endl;

    // As always, let's clean up!
    delete[] d;
}

void UseAuto()
{
    auto a = 10;
    auto b = 10.9;
    auto c = "test";
    auto d = {1, 2, 3, 4, 5};

    // You may use literals to enforce a specific type
    auto e = 42LL;  // "long long {42}" is not possible if not via type alias
    auto f = 42.0f; // equivalent to "float {42.0}"
    auto g = 9UL;   // "unsigned long {42}" is not possible if not via type alias

    typedef long long llong;
    auto h = llong {42};

    auto i = new int[3] {3, 2, 1};
    auto j = std::string {"test"};

    auto k = decltype(a) {};
    decltype(b) l;
    decltype(42) m; // any expression can be used in decltype
    auto n = decltype(a) {987654321LL}; // What the type will be?

    std::cout << "=== with auto ===" << std::endl;
    std::cout << "Type of a is: " << GetTypeId(a) << std::endl;
    std::cout << "Type of b is: " << GetTypeId(b) << std::endl;
    std::cout << "Type of c is: " << GetTypeId(c) << std::endl;
    std::cout << "Type of d is: " << GetTypeId(d) << std::endl;
    std::cout << "Type of e is: " << GetTypeId(e) << std::endl;
    std::cout << "Type of f is: " << GetTypeId(f) << std::endl;
    std::cout << "Type of g is: " << GetTypeId(g) << std::endl;
    std::cout << "Type of h is: " << GetTypeId(h) << std::endl;
    std::cout << "Type of i is: " << GetTypeId(i) << std::endl;
    std::cout << "Type of j is: " << GetTypeId(j) << std::endl;
    std::cout << "Type of k is: " << GetTypeId(k) << std::endl;
    std::cout << "Type of l is: " << GetTypeId(l) << std::endl;
    std::cout << "Type of m is: " << GetTypeId(m) << std::endl;
    std::cout << "Type of n is: " << GetTypeId(n) << std::endl;

    delete[] i;
}

int main()
{
    ExplicitSyntax();
    std::cout << std::endl;
    UseAuto();

    return 0;
}

