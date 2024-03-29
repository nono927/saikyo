cmake_minimum_required(VERSION 3.14)
project(my_project)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()
include(GoogleTest)

include_directories(../ac-library)
include_directories(../src)
add_subdirectory(convolution)
add_subdirectory(data_structure)
add_subdirectory(graph)
add_subdirectory(math_utils)
add_subdirectory(misc)
add_subdirectory(number_theory)
add_subdirectory(string)
add_subdirectory(vector)
