
# We tell the compiler to which files to include (so it knows
# they exist).
include_directories(${SmartPot_SOURCE_DIR}/include)
link_directories(${SmartPot_SOURCE_DIR}/src)

find_package(RapidJSON)

# Set some compile flags (the c++ standard and the multithreading flag)
set(CMAKE_CXX_FLAGS "-std=c++17 -fopenmp")

# We add our main file to the generated binary file.
add_executable(main main.cpp)

# Link with the previously created library.
target_link_libraries(main SmartPotLib pistache crypto ssl pthread mosquitto)