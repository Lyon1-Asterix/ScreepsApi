cmake_minimum_required (VERSION 2.8.8)

project (ScreepsApi)

# JSON
include_directories(../external/json/src)

set (PROJECT_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set (PROJECT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
 
set(PROJECT_SRCS 
    #
    ${PROJECT_SOURCE_DIR}/Data.cpp
    ${PROJECT_SOURCE_DIR}/Node.cpp
    ${PROJECT_SOURCE_DIR}/Module.cpp
    ${PROJECT_SOURCE_DIR}/Client.cpp
    ${PROJECT_SOURCE_DIR}/Api.cpp
    ${PROJECT_SOURCE_DIR}/ApiManager.cpp
)

include_directories("${PROJECT_BINARY_DIR}")
include_directories("${PROJECT_INCLUDE_DIR}")

add_library(${PROJECT_NAME} SHARED ${PROJECT_SRCS})
