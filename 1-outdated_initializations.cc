// SPDX-License-Identifier: MIT
//
// This file demonstrates the different initialization methods that
// pre-existed before the introduction of uniform initialization in C++11.

#include <iostream> // for general input/output operations.

// Provide several Constructors (Ctors) to prove the examples mentioned in
// int main() function.
class Object
{
public:
    Object()
    {
        std::cout << "Object initialized through default Ctor" << std::endl;
    }

    Object(int a)
    {
        std::cout << "Object initialized with one argument:" << std::endl;
        std::cout << "  a: " << a << std::endl;
    }

	Object(int a, float b, std::string c)
	{
        std::cout << "Object initalized with three arguments:" << std::endl;
        std::cout << "  a: " << a << std::endl;
        std::cout << "  b: " << b << std::endl;
        std::cout << "  c: " << c << std::endl;
	}

    Object(int a, int b, int c)
    {
        std::cout << "Object initialized with three integers: ["
                  << a << ", " << b << ", " << c << "]" << std::endl;
    }

    Object(const Object& o)
    {
        std::cout << "Object initialized via Copy-constructor. "
                  << "Address: 0x" << std::hex << &o << std::endl;
    }
};

int main()
{
    // Examples of variable declaration.
    int a;
    float b;
    std::string c;

    // Example of function declaration.
    int testFunction();

    // Example of object initialization with brackets.
    Object d(1, 2.0f, "Hello!");

    // Example of object initialization as variable init.
    // It relies on copy-constructor.
    // TODO: try to compile and run. Do you notice something?
    Object e = 42;

    // Example of object initialization via C aggregate init.
    Object f = {1, 2, 3};

    // Example of object initialization via copy-constructor.
    // TODO: try to compile and run. Do you notice something?
    Object g = Object(4, 2.1f, "Test");
    std::cout << "Address of g: " << std::hex << &g << std::endl;

    // Heap-based object initialization via new keyword.
    Object* h = new Object(5, 3.2f, "Test2");
    std::cout << "Address of h: " << std::hex << h << std::endl;

    // Alternative Heap-based object initialization via new keyword.
    Object* i = new Object;
    std::cout << "Address of i: " << std::hex << i << std::endl;

    // Better clean-up everything in Heap!
    delete h;
    delete i;

	return 0;
}
