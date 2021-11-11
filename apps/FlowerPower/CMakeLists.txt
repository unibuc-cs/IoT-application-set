cmake_minimum_required(VERSION 3.7)

# Setup the project.
project(SmartPot)

# Set our C++ standard.
set(CMAKE_CXX_STANDARD 17)

# Add the subdirectories which we have to compile as follows.
# The src directory which will compile our SmartPot library.
add_subdirectory(src)

# The demo directory with the main app where we call the
# library functionalities.
add_subdirectory(demo)