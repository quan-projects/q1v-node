include_directories(${CMAKE_CURRENT_SOURCE_DIR}/q1v/external/sentry/lib/cmake)

find_package (sentry 0.4.18 REQUIRED COMPONENTS sentry breakpad_client
        PATHS ${CMAKE_CURRENT_SOURCE_DIR}/q1v/external/sentry NO_DEFAULT_PATH)

if( DEFINED SENTRY_DSN )
    if (TARGET sentry::sentry)
        message(STATUS "libsentry loaded")
    endif()
    if (TARGET sentry::breakpad_client)
        message(STATUS "libbreakpad_client loaded")
    endif()
endif()