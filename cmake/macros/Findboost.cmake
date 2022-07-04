if (NOT DEFINED CMAKE_POSITION_INDEPENDENT_CODE)
    add_definitions(-DCMAKE_POSITION_INDEPENDENT_CODE:BOOL=true)
endif (NOT DEFINED CMAKE_POSITION_INDEPENDENT_CODE)
if (NOT DEFINED BOOST_ROOT)
    if (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/q1v/external/boost_1_65_1")
        add_definitions(-DBOOST_ROOT=\"${CMAKE_CURRENT_SOURCE_DIR}/q1v/external/boost_1_65_1\")
    endif ()
endif (NOT DEFINED BOOST_ROOT)

set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_STATIC_RUNTIME ON)
set(Boost_NO_BOOST_CMAKE ON)

find_package(Boost 1.65 REQUIRED COMPONENTS system filesystem thread date_time chrono regex serialization program_options)
if ((${Boost_MAJOR_VERSION} EQUAL 1) AND (${Boost_MINOR_VERSION} EQUAL 54))
    message(SEND_ERROR "Boost version 1.54 is unsupported, more details are available here http://goo.gl/RrCFmA")
endif ()

include_directories(${Boost_INCLUDE_DIRS})
include_directories(SYSTEM ${Boost_INCLUDE_DIRS})

set(Boost_LIBRARIES "${Boost_LIBRARIES};rt")