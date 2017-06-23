project(structarch)
cmake_minimum_required(VERSION 3.9)
enable_testing()

add_executable(tree_tests tests/tree_tests.cpp)

set_property(TARGET tree_tests PROPERTY CXX_STANDARD 17)

add_test(tree-tests tree_tests)


