
include(ExternalProject)

message ( STATUS "in external" )

if(NOT DISABLE_json)
include(ExternalProject)
  ExternalProject_Add(nlohmannjson
    GIT_REPOSITORY https://github.com/nlohmann/json
    GIT_TAG "master"
    BUILD_COMMAND ""
    UPDATE_COMMAND ""
    PATCH_COMMAND ""
    INSTALL_COMMAND ""
    SOURCE_DIR "${CMAKE_SOURCE_DIR}/external/json"
    )
set(Json_INCLUDE_DIRS "${CMAKE_SOURCE_DIR}/external/json/src" PARENT_SCOPE)
endif()
