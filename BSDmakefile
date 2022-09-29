# This is a file that specifies how BSD make should behave to successfully
# compile all our source code. BSD make requires a syntax that differs from 
# GNU make, an equivalent program written for GNU-based systems. Please refer 
# to GNUmakefile if you are on a GNU-based system.

# CXX indicates the compiler of choice. Here you have a default value, which
# is pretty safe given that if you use GNU make, it probably means that you 
# are on a GNU/Linux system with GCC. If you want to override this choice,
# use your environment variables and run make like so:
# 	$ CXX=compiler_of_choice make
CXX ?= clang++

# Here you can find some useful flags that are passed to the compiler.
# -O0: Indicates to never apply any special optimization to boost performances.
#  	   This benefits debugging, as the assembly code will generally reflect the
#  	   structure of your source code.
# --std=c++11: Indicates to adhere to the ISO C++11 standard and exclude any 
#              newer revision, i.e., C++14, C++17, C++20, ...
CXXFLAGS = -O0 --std=c++11 

# Hide a clang warning message relevant for objects initialised by brackets.
.if ${CXX} == "clang++"
CXXFLAGS += -Wno-vexing-parse 
.endif

# On restricted BSD systems, like iOS, exceptions are not available.
# Let's disable them to not have compile errors.
.if ${TERM_PROGRAM} == "a-Shell"
CXXFLAGS += -fno-exceptions
.endif

# Here we use a trick to determine the source code files to be compiled.
# Given that each program corresponds to a source code file, we list all .cc
# files available in the current directory, then substitute the .cc extension
# with the .out extension. And Ta-Da!
PRGS != ls *.cc | sed 's/\.cc/\.out/g'

# Tell BSD make which file suffixes we are treating.
.SUFFIXES: .cc .out

# all: the default task that make will execute if you launch it without
# any further arguments.
all: ${PRGS}

# This task tells how to compile a .cc source code file into a .out executable.
# Indeed, you see a templated command line that will be executed in a shell
# session. Can you guess what will be the final command being executed?
.cc.out:
	${CXX} ${CXXFLAGS} -o $@ $<


# PHONY command in make allows the definition of tasks that are not bound
# to source code files to be compiled.
.PHONY: clean

# In this way we can define a custom command to clean out compiled files.
clean:
	rm -f *.out

