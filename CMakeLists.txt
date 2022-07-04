cmake_minimum_required(VERSION 3.16)

# Required for finding Threads
SET(CMAKE_C_COMPILER_WORKS 1)
SET(CMAKE_CXX_COMPILER_WORKS 1)

include(cmake/macros/settings.cmake)

if (NOT DEFINED ENV{CLION_IDE} AND NOT DEFINED ENV{XCODE_IDE})
    find_program(NINJA_PATH ninja)
    if (NINJA_PATH)
        set(CMAKE_GENERATOR "Ninja" CACHE INTERNAL "")
    endif ()
endif ()

project(${Q1V_PROJECT_NAME})

if ((CMAKE_CXX_COMPILER_ID MATCHES "GNU") OR (CMAKE_CXX_COMPILER_ID MATCHES "Clang"))
    if (CMAKE_CXX_COMPILER_VERSION VERSION_LESS 8)
        message(FATAL_ERROR "GCC version must be at least 8!  " ${CMAKE_CXX_COMPILER_VERSION})
    endif ()
endif ()

if (CMAKE_SYSTEM_PROCESSOR MATCHES "(64)")
    MESSAGE(STATUS "host system: ${CMAKE_SYSTEM_PROCESSOR}")
else ()
    message(FATAL_ERROR "Unrecognized architecture on host system: ${CMAKE_SYSTEM_PROCESSOR}")
endif ()

# Threads
find_package(Threads REQUIRED)

include_directories("${CMAKE_CURRENT_BINARY_DIR}/version")

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/q1v/platform/linux)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/q1v/platform/posix)

include(cmake/macros/flags.cmake)
include(cmake/macros/Findboost.cmake)
include(cmake/macros/Findminiupnpc.cmake)

set(VERSION "")
include(cmake/macros/version.cmake)
add_definitions(-DVERSION=\"${QUAN__VERSION}\")
add_definitions(-DGIT_REVISION=\"${GIT_REVISION}\")

if( DEFINED SENTRY_DSN )
    include(cmake/macros/Findsentry.cmake)
endif( DEFINED SENTRY_DSN )

add_subdirectory(q1v)

