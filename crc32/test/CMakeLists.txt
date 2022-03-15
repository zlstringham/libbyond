add_executable(byondcrc32_test)
target_compile_features(byondcrc32_test PUBLIC cxx_std_11)
target_sources(byondcrc32_test
    PRIVATE
        crc32_test.cc
)
target_link_libraries(byondcrc32_test
    gtest_main
    cpu_features
    byond::crc32
)
