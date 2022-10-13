// SPDX-License-Identifier: MIT
//
// This file demonstrates the resource leak if we do not correctly free all
// ours resources.
//

#include <iostream>

constexpr static const char* MSG = "Hello world!";

// What happens if we forget a delete, like below? Try it out with the
// following command: valgrind <program_name>
void res_leak_example()
{
    auto* ptr = new std::string(MSG);
    std::cout << *ptr << std::endl;

    //delete ptr;
}

// What happens if we have a dangling pointer in place? Can we know what's
// happening if we run the program normally? What happens if we use valgrind?
void dangling_ptr_example()
{
    auto *ptr1 = new std::string(MSG);
    auto *ptr2 = ptr1;

    std::cout << *ptr1 << std::endl;
    delete ptr1;
    std::cout << *ptr2 << std::endl;
}

int main()
{
    //res_leak_example();
    //dangling_ptr_example();
}
