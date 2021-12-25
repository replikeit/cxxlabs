cmake_minimum_required(VERSION 3.20)
project(lab1_cpp)

set(CMAKE_CXX_STANDARD 20)

option(TESTING "Enable testing" ON)

add_subdirectory(src)

if (TESTING)
    enable_testing()
    add_subdirectory(tests)
endif()
