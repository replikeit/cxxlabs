set(SOURCES words_counter.cpp)
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR})

add_library(words-counter STATIC ${SOURCES})
target_include_directories(words-counter INTERFACE ${INCLUDE_DIR})