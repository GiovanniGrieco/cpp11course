// SPDX-License-Identifier: MIT
//
// This file proposes a solution to the following problem.
// We need a program that is subject to this kind of user input:
//      <data_type> <op1> <op2>
// according to <data_type>, output the sum of <opN> if they are numeric, or
// the concatenation of them if they are strings.
//
// E.g.:         <USER_INPUT> => <PROGRAM_OUTPUT>
//    -  "string hello world" => "hello world"
//    -            "int 40 2" => "42"
//    -      "float 3.0 0.14" => "3.14"
//

#include <cstdlib>       // Provides std::exit to terminate the program gracefully.

#include <exception>
#include <functional>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map> // associative array with unique keys.
#include <vector>

// Macro helper to create a lambda function from a given data type and
// conversion function.
#define MakeLambda(TYPE, CONVF)                                 \
    [] (const std::string& op1str, const std::string& op2str) { \
        const TYPE op1 {CONVF(op1str)};                         \
        const TYPE op2 {CONVF(op2str)};                         \
        const SumObj<TYPE> so {op1, op2};                       \
        std::cout << so.Eval() << std::endl;                    \
    }

// Macro helper to create a lambda function from a given data type only.
#define MakeLambdaNoConv(TYPE) MakeLambda(TYPE, )

// Generic data class to store and evaluate the sum of two operands
template<typename T>
class SumObj
{
public:
    SumObj(const T& op1, const T& op2) :
        m_op1 {op1},
        m_op2 {op2}
    { }

    T Eval() const
    {
        return m_op1 + m_op2;
    }

private:
    const T m_op1;
    const T m_op2;
};

// Eval specialization for string, as strings should present a space during
// concatenation.
template<>
std::string SumObj<std::string>::Eval() const
{
    return m_op1 + " " + m_op2;
}

int main(const int argc, const char** argv)
{
    // Define some constants that will be used throughout the scope.
    constexpr static int ARGS_N = 1 /* program name */ + 3 /* user inputs */;
    constexpr static int DT_IDX = 0;
    constexpr static int OP1_IDX = 1;
    constexpr static int OP2_IDX = 2;

    // Associative array that binds together a type name to its conversion lambda
    std::unordered_map<std::string, std::function<void(const std::string&, const std::string&)>>
    supportedTypes {
        {"string", MakeLambdaNoConv(std::string)},
        {"int", MakeLambda(int, std::stoi)},
        {"float", MakeLambda(float, std::stof)}
    };

    // Inline utility to check if a condition is true, otherwise close the program
    // gracefully.
    auto check = [] (bool&& cond, std::string&& msg)
    {
        if (!cond)
        {
            std::cout << msg << std::endl;
            std::exit(EXIT_FAILURE);
        }
    };

    // Inline utility to retrieve the list of supported data types specified in
    // supportedTypes.
    auto supportedTypeKeys = [&] {
        std::ostringstream oss;

        for (auto& pair : supportedTypes)
            oss << pair.first << " ";

        return oss.str();
    };

    check(argc == ARGS_N, "Please insert three arguments in this format: <data_type> <op1> <op2>");

    const std::vector<std::string> args {argv + 1, argv + argc};
    const auto& dt = args[DT_IDX];

    check(supportedTypes.count(dt) == 1, "Unsupported data type: " + dt + ". Supported data types are " + supportedTypeKeys());

    try
    {
        const auto& op1 = args[OP1_IDX];
        const auto& op2 = args[OP2_IDX];
        supportedTypes[dt](op1, op2);
    }
    catch (std::exception const& e)
    {
        std::cout << "ERROR: " << e.what() << std::endl;
        std::exit(EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}

