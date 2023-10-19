cmake_minimum_required(VERSION 3.26)
project(Assignment_2)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

add_executable(Assignment_2 main.cpp src/interior_point.h)

include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG 03597a01ee50ed33e9dfd640b249b4be3799d395
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()
include_directories(src)

add_executable(
        identityMatrixTest
        tests/identityMatrixTest.cpp
)

target_link_libraries(
        identityMatrixTest
        GTest::gtest_main
)

add_executable(
        matrixTransposeTest
        tests/matrixTransposeTest.cpp
)

target_link_libraries(
        matrixTransposeTest
        GTest::gtest_main
)

add_executable(
        augmentedMatrixTest
        tests/augmentedMatrixTest.cpp
)

target_link_libraries(
        augmentedMatrixTest
        GTest::gtest_main
)

add_executable(
        inverseMatrixTest
        tests/inverseMatrixTest.cpp
)

target_link_libraries(
        inverseMatrixTest
        GTest::gtest_main
)

add_executable(
        matrixDetTest
        tests/matrixDetTest.cpp
)

target_link_libraries(
        matrixDetTest
        GTest::gtest_main
)

add_executable(
        solveLinearEqTest
        tests/solveLinearEqTest.cpp
)

target_link_libraries(
        solveLinearEqTest
        GTest::gtest_main
)

add_executable(
        interiorPointTest
        tests/interiorPointTest.cpp
)

target_link_libraries(
        interiorPointTest
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(identityMatrixTest)
gtest_discover_tests(matrixTransposeTest)
gtest_discover_tests(augmentedMatrixTest)
gtest_discover_tests(inverseMatrixTest)
gtest_discover_tests(matrixDetTest)
gtest_discover_tests(solveLinearEqTest)
gtest_discover_tests(interiorPointTest)