include_directories(
        "include"
        "src"
        "external")

file(GLOB_RECURSE Platform platform/linux/system/* platform/posix/system/*)

add_subdirectory(external)
add_subdirectory(src)