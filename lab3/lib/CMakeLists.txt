set(SERVER_LIB rest_service)
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR})

include(FetchContent)

FetchContent_Declare(
        served_lib
        GIT_REPOSITORY https://github.com/meltwater/served
        GIT_TAG        v1.6.0
)
FetchContent_MakeAvailable(served_lib)

FetchContent_GetProperties(served_lib)
if(NOT served_lib_POPULATED)
    FetchContent_Populate(served_lib)
    add_subdirectory(${served_lib_SOURCE_DIR} ${served_lib_BINARY_DIR})
endif()

add_library(served_fake INTERFACE)
target_link_libraries(served_fake INTERFACE served)
target_include_directories(served_fake INTERFACE ${served_lib_SOURCE_DIR}/src)
set(SERVED_LIB served_fake)

FetchContent_Declare(
        json_lib
        GIT_REPOSITORY https://github.com/nlohmann/json
)
FetchContent_MakeAvailable(json_lib)

FetchContent_GetProperties(json_lib)
if(NOT json_lib_POPULATED)
    FetchContent_Populate(json_lib)
    add_subdirectory(${json_lib_SOURCE_DIR} ${json_lib_BINARY_DIR})
endif()

add_library(json_lib_fake INTERFACE)
target_link_libraries(served_fake INTERFACE nlohmann_json)
target_include_directories(json_lib_fake INTERFACE ${json_lib_SOURCE_DIR}/include)
set(JSON_LIB json_lib_fake)

add_library(${SERVER_LIB} STATIC rest_service.cpp)

target_link_libraries(${SERVER_LIB} ${SERVED_LIB})
target_link_libraries(${SERVER_LIB} ${JSON_LIB})
target_include_directories(${SERVER_LIB} INTERFACE ${INCLUDE_DIR})

