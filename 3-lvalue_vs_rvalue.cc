// SPDX-License-Identifier: MIT
//
// This file introduces to the usage of lvalue and rvalue references.

// C++ standard library inclusions
#include <iostream> // General I/O
#include <sstream> // Allows the creation of a string through streams
#include <vector>   // Allows the creation of high-level sequence of objects

// Adds an exclamation to a reference to a mutable lvalue
void AddExclamation(std::string& s)
{
    s += "!";
    // notice that we do not return anything, as we have just operated
    // on the original object that is stored into LvalueReferenceExample stack!
    // => Nothing has been copied so far.
}

// Print a string passed by lvalue reference to const
void PrintLine(const std::string& s)
{
    // Of course, we cannot modify s here, as it is const.
    std::cout << s << std::endl;
}

// In this example we learn how to recognize an lvalue and how its references
// may be used to operate/read on its structure, both locally, and/or in a 
// different scope.
void LvalueReferenceExample()
{
    std::string s {"Hello"};   // s is an lvalue
    std::string& r1 = s;       // lvalue reference to s
    const std::string& r2 = s; // lvalue reference to constant s

    r1 += " world"; // mutable ref => s is modified
    //r2 += "!";    // error: constant ref => cannot modify s through reference to const
    std::cout << r2 << std::endl; // prints s, modified by r1

    AddExclamation(r1);
    PrintLine(r2);
}

// Retrieve the value at given index as a lvalue reference
int& at(std::vector<int>& arr, size_t index)
{
    return arr[index]; // NOTE: this will be a lvalue reference!
}

// Given an lvalue reference to const vector, print its values to a string,
// then return it (as a copy).
// NOTE: Why we cannot return an lvalue reference? How can we fix?
const std::string PrintVector(const std::vector<int>& v)
{
    std::ostringstream x;
    
    x << "[";
    for (auto& el : v)
        x << el << ",";
    x << "]";

    return x.str();
}

void LvalueReturnedReferenceExample()
{
    std::vector<int> arr {1, 2, 3};
    at(arr, 1) = 0; // Given that at(..) returns an lvalur reference, 
                    // it can be used for an lvalue expression!

    std::cout << "arr = " << PrintVector(arr) << std::endl;
}

void RvalueReferenceExample()
{
    std::string s1 = "Hello";

    // error: cannot bind non-const lvalue reference to an rvalue.
    // In this case it is an xvalue, a temporary.
    //std::string& r1 = s1 + s1; 
                                 
    // However, we can extend the lifetime of the xvalue through a lvalue 
    // reference to const.
    const std::string& r1 = s1 + " World";

    // alternatively, we use rvalue references! And they can be mutable!
    std::string&& r2 = s1 + " World";
    r2 += "!";

    std::cout << r1 << std::endl;
    std::cout << r2 << std::endl;
}

// Example of an object with overload constructors for move semantics.
class Object
{
public:
    Object(int& x)
    {
        std::cout << "Ctor overload with lvalue reference called. x = " << x << std::endl;
    }

    Object(const int& x)
    {
        std::cout << "Ctor overload with lvalue reference to const called. x = " << x << std::endl;
    }

    Object(int&& x)
    {
        std::cout << "Ctor overload with rvalue reference called. x = " << x << std::endl;
    }
};

const std::string PrintVector(std::vector<int>&& v)
{
    std::ostringstream x;
    std::vector<int> vlocal {std::move(v)};
    
    x << "[";
    for (auto& el : vlocal)
        x << el << ",";
    x << "]";

    return x.str();
}

void RvalueOverloadExample()
{
    // Remember that literals are rvalues
    Object {42};

    int x = 1;
    Object {x};

    const int& cx = x;
    Object {cx};

    // we don't use x anymore, let's convert it to rvalue and move to Object.
    Object {std::move(x)};

    // Let's return to printing a vector, but now with a twist...
    // Can you justify this behaviour?
    std::vector<int> y {1,2,3};
    auto s = PrintVector(std::move(y));
    std::cout << s << std::endl;
    std::cout << "Is vector y empty? " << std::boolalpha << y.empty() << std::endl;
    // Why y.empty() returns that value?
}

int main()
{
    std::cout << "=== LvalueReferenceExample ===" << std::endl;
    LvalueReferenceExample();
    std::cout << std::endl;

    std::cout << "=== LvalueReturnedReferenceExample ===" << std::endl;
    LvalueReturnedReferenceExample();
    std::cout << std::endl;

    std::cout << "=== RvalueReferenceExample ===" << std::endl;
    RvalueReferenceExample();
    std::cout << std::endl;

    std::cout << "=== RvalueOverloadExample ===" << std::endl;
    RvalueOverloadExample();
    std::cout << std::endl;

    return 0;
}

