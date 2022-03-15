add_library(byondcrc32 "")
set_property(TARGET byondcrc32 PROPERTY C_STANDARD 99)
target_include_directories(byondcrc32
    PUBLIC "${CMAKE_CURRENT_LIST_DIR}/include"
)
target_sources(byondcrc32
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/include/byond/crc32.h
    PRIVATE
        src/tables.h
        src/lut_impl.h
        src/combine.c
        src/crc32.c
)
add_library(byond::crc32 ALIAS byondcrc32)

if (BUILD_TESTING)
    add_subdirectory(test)
endif()
