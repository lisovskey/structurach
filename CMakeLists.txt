project(structarch)
cmake_minimum_required(VERSION 3.11)
enable_testing()

add_executable(sort_tests tests/sort_tests.cpp)
add_executable(tree_tests tests/tree_tests.cpp)

set_property(TARGET sort_tests PROPERTY CXX_STANDARD 14)
set_property(TARGET tree_tests PROPERTY CXX_STANDARD 17)

add_test(sort-tests sort_tests)
add_test(tree-tests tree_tests)
