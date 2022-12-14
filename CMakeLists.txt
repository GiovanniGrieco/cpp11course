# SPDX-License-Identifier: MIT
#
# This file demonstrates the usage of CMake build system to compile
# these examples.

# CMake will refuse to build if actual installed version is older than the one
# specified hereby. This lower bound allows us to use CMake newer features.
# More info: https://cmake.org/cmake/help/latest/command/cmake_minimum_required.html
cmake_minimum_required(VERSION 2.8.11)

# Give this project a name. This name will be used, as an example, to generate
# a Visual Studio Solution on Windows.
# More info: https://cmake.org/cmake/help/latest/command/project.html
project(CppCourseExamples)

# Given that we want an executable for each source code file under this
# directory, use file function with GLOB to select all files with extension cc.
# "SourceFiles" is the output variable, which will be an array of file names.
# More info: https://cmake.org/cmake/help/latest/command/file.html
file(GLOB SourceFiles *.cc)

# Here you can find some useful flags that are passed to the compiler.
# -O0: Indicates to never apply any special optimization to boost performances.
#  	   This benefits debugging, as the assembly code will generally reflect the
#  	   structure of your source code.
# --std=c++11: Indicates to adhere to the ISO C++11 standard and exclude any
#              newer revision, i.e., C++14, C++17, C++20, ... and GNU dialects.
# -fno-elide-constructors: Indicates to not optimize copy assignments.
add_compile_options(-O0 --std=c++11 -fno-elide-constructors)

# Let's now loop over each source file. "file_path" is the iterator variable.
# More info: https://cmake.org/cmake/help/latest/command/foreach.html
foreach(file_path ${SourceFiles})
    # And remove the .cc extension from the filename to make a proper executable name.
    # Save the output in varialbe "new_name".
    string(REPLACE ".cc" "" new_name ${file_path})
    # Ensure we get the filename only, without its path.
    # More info: https://cmake.org/cmake/help/latest/command/get_filename_component.html
    get_filename_component(filename ${new_name} NAME)
    # Finally, tell CMake to make an executable named by the variable
    # "filename" from the source code indicated by "file_path".
    # More info: https://cmake.org/cmake/help/latest/command/add_executable.html
    add_executable(${filename} ${file_path})
endforeach()
