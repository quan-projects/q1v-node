set(Q1V_PROJECT_NAME "q1v")
set(Q1V_PROJECT_VENDOR "Quan Project")
set(Q1V_PROJECT_DOMAIN "quan-project.com")
set(Q1V_PROJECT_MAIL "contato@${Q1V_PROJECT_DOMAIN}")
set(Q1V_PROJECT_URL "https://${Q1V_PROJECT_DOMAIN}")
set(Q1V_CURRENCY_DISPLAY_NAME "Asset QUAN First Version")
set(Q1V_CURRENCY_TICKER "Q1V")
set(Q1V_VERSION_BUILD_NO 1)

if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/VERSION")
    file(READ "${CMAKE_CURRENT_SOURCE_DIR}/VERSION" VERSION_RAW)
    string(STRIP "${VERSION_RAW}" Q1V_VERSION)
    string(REPLACE "." ";" VERSION_LIST ${Q1V_VERSION})
    list(GET VERSION_LIST 0 Q1V_VERSION_MAJOR)
    list(GET VERSION_LIST 1 Q1V_VERSION_MINOR)
    list(GET VERSION_LIST 2 Q1V_VERSION_REV)
else()
    set(Q1V_VERSION 3.0.0)
    set(Q1V_VERSION_MAJOR 3)
    set(Q1V_VERSION_MINOR 0)
    set(Q1V_VERSION_REV 0)
endif()

set(Q1V_RELEASE_NAME "Lothim-${Q1V_PROJECT_NAME}")