include(ExternalProject)

macro ( FindOrCloneExternal name repository args varprefix )
    find_package ( ${name} QUIET
        NO_DEFAULT_PATH
        NO_CMAKE_ENVIRONMENT_PATH
        NO_CMAKE_PATH
        NO_SYSTEM_ENVIRONMENT_PATH
        NO_CMAKE_PACKAGE_REGISTRY
        NO_CMAKE_BUILDS_PATH
        NO_CMAKE_SYSTEM_PATH
        NO_CMAKE_SYSTEM_PACKAGE_REGISTRY
    )
    if (NOT ${name}_FOUND)
        ExternalProject_Add(${name}
            GIT_REPOSITORY ${repository}
            GIT_TAG "master"
            SOURCE_DIR "${CMAKE_SOURCE_DIR}/external/${name}"
            CMAKE_ARGS ${args}  -DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}
        )
        set(${varprefix}_INCLUDE_DIR "${CMAKE_BINARY_DIR}/include")
        set(${varprefix}_LIBRARY_DIR "${CMAKE_BINARY_DIR}/lib")
        set(${varprefix}_LIBRARIES "${CMAKE_SHARED_LIBRARY_PREFIX}${varprefix}${CMAKE_SHARED_LIBRARY_SUFFIX}")
    endif ()
endmacro ()

FindOrCloneExternal ( nlohmann_json https://github.com/Lyon1-Asterix/json "-DBuildTests=OFF" JSON )