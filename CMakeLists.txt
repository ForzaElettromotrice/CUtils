cmake_minimum_required(VERSION 3.25)
project(CUtils C)

set(CMAKE_C_STANDARD 17)

set(BUILD_SHARED "Build shared libraries instead of static" ON)
set(DEBUG_FLAG "Allow debug prints" ON)

if (DEBUG_FLAG)
    add_compile_definitions(Debug)
endif ()


set(LIB_TYPE STATIC)
if (BUILD_SHARED)
    set(LIB_TYPE SHARED)
endif ()

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/lib/xxHash/cmake_unofficial ${CMAKE_CURRENT_SOURCE_DIR}/lib/xxHash/lib EXCLUDE_FROM_ALL)

add_library(CUtils ${LIB_TYPE}
        src/queue.c
        src/hashmap.c
        src/logger.c)


if (BUILD_SHARED)
    set_target_properties(CUtils PROPERTIES
            LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib/CUtils
            OUTPUT_NAME CUtils)
else ()
    set_target_properties(CUtils PROPERTIES
            ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib/CUtils
            OUTPUT_NAME CUtils)
endif ()

target_include_directories(CUtils
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/CUtils
        PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/include)

target_link_libraries(
        CUtils PUBLIC xxHash::xxhash
)
