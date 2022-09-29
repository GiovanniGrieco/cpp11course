# This is a file that specifies how GNU make should behave to successfully
# compile all our source code. GNU make requires a syntax that differs from 
# BSD make, an equivalent program written for BSD-based systems. Please refer 
# to BSDmakefile if you are on a BSD-based system.

# CXX indicates the compiler of choice. Here you have a default value, which
# is pretty safe given that if you use GNU make, it probably means that you 
# are on a GNU/Linux system with GCC. If you want to override this choice,
# use your environment variables and run make like so:
# 	$ CXX=compiler_of_choice make
CXX ?= g++
# Here you can find some useful flags that are passed to the compiler.
# -O0: Indicates to never apply any special optimization to boost performances.
#  	   This benefits debugging, as the assembly code will generally reflect the
#  	   structure of your source code.
# --std=c++11: Indicates to adhere to the ISO C++11 standard and exclude any 
#              newer revision, i.e., C++14, C++17, C++20, ... and GNU dialects.
CXXFLAGS = -O0 --std=c++11 

# all: the default task that make will execute if you launch make without 
#      any further arguments.
#      Here we use a trick: wildcard will search in the current directory for
#      the files that match our criteria, in this case *.cc. Furthermore,
#      patsubst substitutes the .cc extension to .out. In this way we tell
#      make to compile all the source code available and generate one
#      executable per source file.
all: $(patsubst %.cc,%.out,$(wildcard *.cc))

# This task tells how to arrive to a .out compiled file from a .cc source code
# one. Indeed, you see a templated command line that will be executed in a
# shell session. Can you guess what will be the final command being executed?
%.out: %.cc 
	$(CXX) $(CXXFLAGS) -o $@ $<

# PHONY command in make allows the definition of tasks that are not bound
# to source code files to be compiled.
.PHONY: clean

# In this way we can define a custom command to clean out compiled files.
clean:
	rm -f *.out

