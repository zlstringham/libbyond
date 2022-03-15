cmake_minimum_required(VERSION 3.11)

# option() honors normal variables.
# see: https://cmake.org/cmake/help/git-stage/policy/CMP0077.html
if(POLICY CMP0077)
  cmake_policy(SET CMP0077 NEW)
endif()

project(libbyond
    VERSION 0.1.0
    LANGUAGES C
)

list(APPEND CMAKE_MODULE_PATH
  ${CMAKE_CURRENT_LIST_DIR}/cmake
)

include(DownloadGTest)
include(DownloadBenchmark)
include(DownloadCpuFeatures)
include(CTest)

if (BUILD_TESTING)
  enable_language(CXX)
endif ()

add_subdirectory(crc32)
