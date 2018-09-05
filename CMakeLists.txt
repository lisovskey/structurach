project(structarch)
cmake_minimum_required(VERSION 3.11)
enable_testing()

add_executable(sort_tests tests/sort_tests.cpp)
add_executable(map_tests tests/map_tests.cpp)
add_executable(blockchain_tests blockchain/blockchain_tests.cpp)

set_property(TARGET sort_tests PROPERTY CXX_STANDARD 14)
set_property(TARGET map_tests PROPERTY CXX_STANDARD 17)
set_property(TARGET blockchain_tests PROPERTY CXX_STANDARD 17)

add_test(sort-tests sort_tests)
add_test(map-tests map_tests)
add_test(blockchain-tests blockchain_tests)
