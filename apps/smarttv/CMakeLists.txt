cmake_minimum_required(VERSION 3.16)
project(smart-tv)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -lpthread -pthread -lmosquitto")

find_package(nlohmann_json 3.7.0 REQUIRED)
find_package(PkgConfig)
find_package(Boost 1.40 COMPONENTS program_options REQUIRED)

pkg_check_modules(Mosquitto REQUIRED IMPORTED_TARGET libmosquitto)

add_executable(${PROJECT_NAME} main.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC ${smart-tv_SOURCE_DIR}/../../pistache/include)
target_link_libraries(${PROJECT_NAME} PUBLIC nlohmann_json::nlohmann_json ${smart-tv_SOURCE_DIR}/../../pistache/build/src/libpistache.so PkgConfig::Mosquitto ssl crypto Boost::program_options)
