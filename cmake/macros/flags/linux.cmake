# This option has no effect in glibc version less than 2.20.
# Since glibc 2.20 _BSD_SOURCE is deprecated, this macro is recomended instead
add_definitions("-D_DEFAULT_SOURCE -D_GNU_SOURCE")

set(ARCH native CACHE STRING "CPU to build for: -march value or default")
if ("${ARCH}" STREQUAL "default")
    set(ARCH_FLAG "")
else ()
    set(ARCH_FLAG "-march=${ARCH}")
endif ()

set(WARNINGS "-Wall -Wextra -Wpointer-arith -Wundef -Wvla -Wwrite-strings -Werror -Wno-error=extra -Wno-error=unused-function -Wno-error=deprecated-declarations -Wno-error=sign-compare -Wno-error=strict-aliasing -Wno-error=type-limits -Wno-unused-parameter -Wno-error=unused-variable -Wno-error=undef -Wno-error=uninitialized -Wno-error=unused-result -Wno-unknown-pragmas -Wno-clobbered -Wno-error=class-memaccess")

if (CMAKE_C_COMPILER_ID STREQUAL "Clang")
    set(WARNINGS "${WARNINGS} -Wno-error=mismatched-tags -Wno-error=null-conversion -Wno-overloaded-shift-op-parentheses -Wno-error=shift-count-overflow -Wno-error=tautological-constant-out-of-range-compare -Wno-error=unused-private-field -Wno-error=unneeded-internal-declaration -Wno-error=missing-braces")
else ()
    set(WARNINGS "${WARNINGS} -Wlogical-op -Wno-error=maybe-uninitialized -Wno-error=unused-but-set-variable")
endif ()

if (CMAKE_C_COMPILER_ID STREQUAL "GNU")
    set(WARNINGS "${WARNINGS} -Wno-error=odr -Wno-format-truncation")
endif ()

set(C_WARNINGS "-Waggregate-return -Wnested-externs -Wold-style-definition -Wstrict-prototypes")
set(CXX_WARNINGS "-Wno-reorder -Wno-missing-field-initializers")

try_compile(STATIC_ASSERT_RES "${CMAKE_CURRENT_BINARY_DIR}/static-assert" "${CMAKE_CURRENT_SOURCE_DIR}/cmake/test-static-assert.c" COMPILE_DEFINITIONS "-std=c11")
if (STATIC_ASSERT_RES)
    set(STATIC_ASSERT_FLAG "")
else ()
    set(STATIC_ASSERT_FLAG "-Dstatic_assert=_Static_assert")
endif ()

try_compile(STATIC_ASSERT_CPP_RES "${CMAKE_CURRENT_BINARY_DIR}/static-assert" "${CMAKE_CURRENT_SOURCE_DIR}/cmake/test-static-assert.cpp" COMPILE_DEFINITIONS "-std=c++11")
if (STATIC_ASSERT_CPP_RES)
    set(STATIC_ASSERT_CPP_FLAG "")
else ()
    set(STATIC_ASSERT_CPP_FLAG "-Dstatic_assert=_Static_assert")
endif ()

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c11 ${WARNINGS} ${C_WARNINGS} ${ARCH_FLAG} -maes")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 ${STATIC_ASSERT_CPP_FLAG} ${WARNINGS} ${CXX_WARNINGS} ${ARCH_FLAG} -maes")

if (CMAKE_CXX_COMPILER_VERSION VERSION_GREATER_EQUAL 9)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-error=deprecated-copy -Wno-error=redundant-move")
endif ()
if (CMAKE_C_COMPILER_VERSION VERSION_GREATER_EQUAL 9)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-error=deprecated-copy -Wno-error=redundant-move")
endif ()

if (CMAKE_C_COMPILER_ID STREQUAL "GNU")
    set(DEBUG_FLAGS "-g3 -Og")
endif ()

set(RELEASE_FLAGS "-Ofast -DNDEBUG -Wno-unused-variable")

if (NOT DEFINED USE_LTO_DEFAULT)
    set(USE_LTO_DEFAULT false)
endif ()
set(USE_LTO ${USE_LTO_DEFAULT} CACHE BOOL "Use Link-Time Optimization (Release mode only)")

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    # There is a clang bug that does not allow to compile code that uses AES-NI intrinsics if -flto is enabled, so explicitly disable
    set(USE_LTO false)
endif ()

if (USE_LTO)
    set(RELEASE_FLAGS "${RELEASE_FLAGS} -flto")
    if (STATIC)
        set(RELEASE_FLAGS "${RELEASE_FLAGS} -ffat-lto-objects")
    endif ()
    if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU" AND NOT OPENBSD AND NOT DRAGONFLY)
        if (DEFINED CHOST)
            set(CMAKE_AR "${CHOST}-gcc-ar")
            set(CMAKE_RANLIB "${CHOST}-gcc-ranlib")
        else ()
            set(CMAKE_AR "gcc-ar")
            set(CMAKE_RANLIB "gcc-ranlib")
        endif ()
    endif ()
endif ()


set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} ${DEBUG_FLAGS}")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${DEBUG_FLAGS}")
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} ${RELEASE_FLAGS}")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} ${RELEASE_FLAGS}")

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static-libgcc -static-libstdc++")