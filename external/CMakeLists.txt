include(ExternalProject)

if(NOT DISABLE_json)
    find_package ( nlohmann_json QUIET
        NO_DEFAULT_PATH
        NO_CMAKE_ENVIRONMENT_PATH
        NO_CMAKE_PATH
        NO_SYSTEM_ENVIRONMENT_PATH
        NO_CMAKE_PACKAGE_REGISTRY
        NO_CMAKE_BUILDS_PATH
        NO_CMAKE_SYSTEM_PATH
        NO_CMAKE_SYSTEM_PACKAGE_REGISTRY
    )
    if (NOT nlohmann_json_FOUND)
        ExternalProject_Add(nlohmann_json
            GIT_REPOSITORY https://github.com/nlohmann/json
            GIT_TAG "master"
            SOURCE_DIR "${CMAKE_SOURCE_DIR}/external/nlohmann_json"
            CMAKE_ARGS -DBuildTests=OFF  -DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}
        )
        set(JSON_INCLUDE_DIR "${CMAKE_BINARY_DIR}/include" PARENT_SCOPE)
    endif ()
endif()
