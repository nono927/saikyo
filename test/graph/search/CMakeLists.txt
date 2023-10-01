add_executable(bfs_test bfs_test.cpp)
target_link_libraries(bfs_test GTest::gtest_main)
gtest_discover_tests(bfs_test)

add_executable(dfs_all_test dfs_all_test.cpp)
target_link_libraries(dfs_all_test GTest::gtest_main)
gtest_discover_tests(dfs_all_test)

add_executable(dfs_test dfs_test.cpp)
target_link_libraries(dfs_test GTest::gtest_main)
gtest_discover_tests(dfs_test)
