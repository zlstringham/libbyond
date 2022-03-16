add_executable(byondcrc32_bench crc32_bench.cc)
target_compile_features(byondcrc32_bench PUBLIC cxx_std_11)
target_link_libraries(byondcrc32_bench
  benchmark_main
  byond::crc32
)
