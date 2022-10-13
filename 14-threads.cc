// SPDX-License-Identifier: MIT
//
// This file demonstrates the use of threads by relying on the C++ low-level
// multithreading interface.
//

#include <chrono>
#include <exception>
#include <iostream>
#include <random>
#include <thread>

// Source: https://en.wikipedia.org/wiki/Primality_test#C,_C++,_C#_&_D
bool IsPrime(int n)
{
    if (n == 2 || n == 3)
        return true;

    if (n <= 1 || n % 2 == 0 || n % 3 == 0)
        return false;

    for (int i = 5; i * i <= n; i += 6)
        if (n % i == 0 || n % (i + 2) == 0)
            return false;

    return true;
}

void GenRndPrime(const long unsigned seed)
{
    constexpr static int UID_MIN = 10;
    constexpr static int UID_MAX = 1e5;

    try
    {
        std::cout << "TID " << std::this_thread::get_id() << " started" << std::endl;

        std::default_random_engine dre {seed};
        std::uniform_int_distribution<int> uid {UID_MIN, UID_MAX};
        int n {};

        do 
        {
            n = uid(dre);
        }
        while (!IsPrime(n));

        std::cout << "TID " << std::this_thread::get_id() << " found prime: " << n << std::endl;
    }
    // make sure no exception leaves the thread
    // as it would call std::terminate() and abort
    // program execution
    catch (const std::exception& e)
    {
        std::cerr << "ERROR [TID " << std::this_thread::get_id() << "] " 
                  << e.what() << std::endl;
    }
    catch (...)
    {
        std::cerr << "ERROR [TID " << std::this_thread::get_id() << "] " << std::endl;
    }
}

int main()
{
    try
    {
        std::cout << "Program with TID " << std::this_thread::get_id() << " started" << std::endl;

        std::thread t1 {GenRndPrime, 42};
        std::cout << "Launched TID " << t1.get_id() << std::endl;

        std::thread t2 {GenRndPrime, 200};
        std::cout << "Launched TID " << t2.get_id() << std::endl;

        t2.detach();
        std::cout << "Waiting for TID " << t1.get_id() << std::endl;
        t1.join();

        std::cout << "Finished!" << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cerr << "Exception in main thread TID " << std::this_thread::get_id() << ": " << e.what() << std::endl;
    }
}

