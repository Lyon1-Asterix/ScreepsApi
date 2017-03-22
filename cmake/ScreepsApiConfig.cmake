
get_filename_component(SELF_DIR "${CMAKE_CURRENT_LIST_FILE}" PATH)
get_filename_component(ScreepsApi_INCLUDE_DIRS "${SELF_DIR}/../include" ABSOLUTE)
get_filename_component(ScreepsApi_LIBRARY_DIRS "${SELF_DIR}/../lib" ABSOLUTE)
set(ScreepsApi_LIBRARIES "${CMAKE_SHARED_LIBRARY_PREFIX}ScreepsApi${CMAKE_SHARED_LIBRARY_SUFFIX}")
