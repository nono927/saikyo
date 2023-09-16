add_executable(digits_test digits_test.cpp)
target_link_libraries(digits_test GTest::gtest_main)
gtest_discover_tests(digits_test)

add_executable(log2_test log2_test.cpp)
target_link_libraries(log2_test GTest::gtest_main)
gtest_discover_tests(log2_test)

add_executable(overflow_test overflow_test.cpp)
target_link_libraries(overflow_test GTest::gtest_main)
gtest_discover_tests(overflow_test)

add_executable(radix_test radix_test.cpp)
target_link_libraries(radix_test GTest::gtest_main)
gtest_discover_tests(radix_test)
