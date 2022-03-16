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
target_link_libraries(byondcrc32
    cpu_features
)
# Add SIMD headers and compiler flags.
if (CMAKE_SYSTEM_PROCESSOR MATCHES "(x86_64)|(AMD64|amd64)|(^i.86$)")
    target_sources(byondcrc32 PRIVATE src/pclmul_impl.h)
    if (MSVC)
        target_compile_options(byondcrc32 PRIVATE /arch:AVX)
    else()
        target_compile_options(byondcrc32 PRIVATE -mpclmul -msse4.1)
    endif()
endif()
add_library(byond::crc32 ALIAS byondcrc32)

if (BUILD_TESTING)
    add_subdirectory(test)
endif()
