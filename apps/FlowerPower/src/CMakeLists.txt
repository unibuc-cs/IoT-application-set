# We tell CMake what directory to include for the headers.
# CARE! the SmartPot prefix is the NAME OF OUR PROJECT we set
# up in the root directory.
include_directories(${SmartPot_SOURCE_DIR}/include)

# Create a variable with our src directory name.
set(SRC_DIR ${SmartPot_SOURCE_DIR}/src)

set(CMAKE_CXX_FLAGS "-std=c++17 -fopenmp")

# Set the files which shall be included in the library.
set(SRC_FILES   ${SRC_DIR}/Sensor.cpp
                ${SRC_DIR}/Plant.cpp
                ${SRC_DIR}/SmartPot.cpp
                ${SRC_DIR}/SmartPotEndpoint.cpp
)

# We add the source files we want to have in the library.
add_library(SmartPotLib ${SRC_FILES})