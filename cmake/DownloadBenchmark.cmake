include(FetchContent)

FetchContent_Declare(
  benchmark
  GIT_REPOSITORY https://github.com/google/benchmark.git
  GIT_TAG        0d98dba29d66e93259db7daa53a9327df767a415 # v1.6.1
)
FetchContent_MakeAvailable(benchmark)

if(IS_DIRECTORY "${benchmark_SOURCE_DIR}")
    set_property(DIRECTORY ${benchmark_SOURCE_DIR} PROPERTY EXCLUDE_FROM_ALL YES)
endif()
