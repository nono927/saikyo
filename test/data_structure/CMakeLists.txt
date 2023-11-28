add_executable(binary_trie_test binary_trie_test.cpp)
target_link_libraries(binary_trie_test GTest::gtest_main)
gtest_discover_tests(binary_trie_test)

add_executable(doubling_test doubling_test.cpp)
target_link_libraries(doubling_test GTest::gtest_main)
gtest_discover_tests(doubling_test)

add_executable(matrix_test matrix_test.cpp)
target_link_libraries(matrix_test GTest::gtest_main)
gtest_discover_tests(matrix_test)

add_executable(sorted_array_test sorted_array_test.cpp)
target_link_libraries(sorted_array_test GTest::gtest_main)
gtest_discover_tests(sorted_array_test)
