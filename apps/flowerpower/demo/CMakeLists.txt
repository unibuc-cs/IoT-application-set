
# We tell the compiler to which files to include (so it knows
# they exist).
include_directories(${SmartPot_SOURCE_DIR}/include)
link_directories(${SmartPot_SOURCE_DIR}/src)

find_package(RapidJSON)
find_package(Boost 1.40 COMPONENTS program_options REQUIRED)

# Set some compile flags (the c++ standard and the multithreading flag)
set(CMAKE_CXX_FLAGS "-std=c++17 -fopenmp")

# We add our main file to the generated binary file.
add_executable(main main.cpp)

target_include_directories(main PUBLIC ${SmartPot_SOURCE_DIR}/../../pistache/include)

# Link with the previously created library.
target_link_libraries(main PUBLIC SmartPotLib crypto ssl pthread mosquitto Boost::program_options ${SmartPot_SOURCE_DIR}/../../pistache/build/src/libpistache.so)

