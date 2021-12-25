set(SOURCES json.cpp)
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR})

add_library(json-lib STATIC ${SOURCES})
target_include_directories(json-lib INTERFACE ${INCLUDE_DIR})