cmake_minimum_required(VERSION 3.3)

project (ScreepsApi)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g -ggdb")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

option(DISABLE_json "bla bla bla ... nlhomann/json" OFF)

add_subdirectory(external)
include_directories(${Json_INCLUDE_DIRS})

set (PROJECT_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set (PROJECT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
 
file(
        GLOB_RECURSE
        PROJECT_SRCS
        ${PROJECT_SOURCE_DIR}/*
)

file(
        GLOB_RECURSE
        PROJECT_PUBLIC_HEADERS
        ${PROJECT_INCLUDE_DIR}/*
)

include_directories("${PROJECT_BINARY_DIR}")
include_directories("${PROJECT_INCLUDE_DIR}")

add_library(${PROJECT_NAME} SHARED ${PROJECT_SRCS})

if(NOT DISABLE_json)
add_dependencies(${PROJECT_NAME} nlohmannjson)
endif ()

#INSTALL(TARGETS ${PROJECT_NAME}
#  RUNTIME DESTINATION bin
#  LIBRARY DESTINATION lib
#  ARCHIVE DESTINATION lib
#)

install(FILES ${PROJECT_PUBLIC_HEADERS} DESTINATION include/${PROJECT_NAME})
install(TARGETS ${PROJECT_NAME} DESTINATION lib)
install(FILES cmake/${PROJECT_NAME}-Config.cmake DESTINATION lib/cmake)