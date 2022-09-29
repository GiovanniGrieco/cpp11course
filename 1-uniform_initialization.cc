// SPDX-License-Identifier: MIT
//
// This file demonstrates the usage of C++11 uniform initialization and its
// std::initializer_list<T> proxy container.

// C standard library inclusions
#include <cassert>          // assert() aborts the program if the given
                            // condition is not true.

// C++ standard library inclusions
#include <initializer_list> // C++11 std::initializer_list<T> definition.
#include <iostream>         // for general input/output operations.

// DataStore provides a C++ high level access to array of SIZE elements to
// demonstrate C++11 uniform initialization and std::initializer_list<T> usage.
class DataStore
{
public:
    static constexpr int SIZE = 10;

    // Constructor that supports a braced list of elements as arguments.
    DataStore(std::initializer_list<int> values)
    {
        assert(values.size() < SIZE);
        for (auto& v : values)
            Add(v);
    }

    // Add a new element to the array by pushing it at the end of it.
    void Add(int value)
    {
        assert(m_size < SIZE);
        m_arr[m_size++] = value;
    }

    // Remove the most recent element from the array.
    void Remove()
    {
        --m_size;
        // TODO: What may be wrong with this implementation?
        // Can you fix it?
    }

    int operator [](int index)
    {
        // TODO: What may be wrong with this implementation?
        // Can you fix it?
        return m_arr[index];
    }

    int GetSize() const
    {
        return m_size;
    }

private:
    // TODO: Notice the uniform initialization here! 
    // What values will be placed when object is initialized?
    int m_arr[SIZE];
    int m_size {};
};

class DifferentDataTypes
{
public:
    DifferentDataTypes(std::string a, int b, float c) :
        m_a {a}, // TODO: what we have here!
        m_b {b},
        m_c {c}
    {
        // we don't need to make nothing more.
    }

    std::string GetA() const
    {
        return m_a;
    }

    int GetB() const
    {
        return m_b;
    }

    float GetC() const
    {
        return m_c;
    }

private:
    std::string m_a;
    int m_b;
    float m_c;
};

int main()
{
    // Some examples of uniform initialization with simple data types
    // and std::string standard object.
    int x {0};  
    float y {4.2f};
    int a[5] {1,2,3,4,5};
    std::string s {"Hello world!"};
    // as you may notice, direct initialization becomes the same
    // for all data types!
    
    // The same criteria is applied for custom objects
    DataStore ds {1,2,3,42};
    std::cout << "DataStore content: [";
    for (int i = 0; i < ds.GetSize(); ++i)
        std::cout << ds[i] << ", ";
    std::cout << "]" << std::endl;

    // What if we have different argument types?
    DifferentDataTypes ddt {"Hello!", 42, 1.5};
    std::cout << "DifferentDataTypes content: " << std::endl;
    std::cout << "\t a: " << ddt.GetA() << std::endl;
    std::cout << "\t b: " << ddt.GetB() << std::endl;
    std::cout << "\t c: " << ddt.GetC() << std::endl;

    return 0;
}

