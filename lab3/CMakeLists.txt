include(FetchContent)

cmake_minimum_required(VERSION 3.20)
project(lab3)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(lib)

add_executable(main main.cpp)
target_link_libraries(main rest_service)