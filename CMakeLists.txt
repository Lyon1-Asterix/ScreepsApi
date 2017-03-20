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
 
set(PROJECT_SRCS 
    #
    ${PROJECT_SOURCE_DIR}/Node.cpp
    ${PROJECT_SOURCE_DIR}/Module.cpp
    ${PROJECT_SOURCE_DIR}/Client.cpp
    ${PROJECT_SOURCE_DIR}/Api.cpp
    ${PROJECT_SOURCE_DIR}/ApiManager.cpp
)

include_directories("${PROJECT_BINARY_DIR}")
include_directories("${PROJECT_INCLUDE_DIR}")

add_library(${PROJECT_NAME} SHARED ${PROJECT_SRCS})

if(NOT DISABLE_json)
add_dependencies(${PROJECT_NAME} nlohmannjson)
endif ()

INSTALL(TARGETS ${PROJECT_NAME}
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
)