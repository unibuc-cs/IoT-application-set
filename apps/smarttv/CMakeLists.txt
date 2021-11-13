cmake_minimum_required(VERSION 3.16)
project(smart-tv)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -lpthread -pthread -lmosquitto")

find_package(nlohmann_json 3.7.0 REQUIRED)
find_package(PkgConfig)
pkg_check_modules(Pistache REQUIRED IMPORTED_TARGET libpistache)
pkg_check_modules(Mosquitto REQUIRED IMPORTED_TARGET libmosquitto)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} nlohmann_json::nlohmann_json PkgConfig::Pistache PkgConfig::Mosquitto ssl crypto)