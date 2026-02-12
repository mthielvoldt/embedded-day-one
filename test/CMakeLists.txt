cmake_minimum_required(VERSION 3.25)
set(CMAKE_POLICY_VERSION_MINIMUM 3.25)

add_compile_options("-g")

project(zero_test LANGUAGES CXX C)

include(FetchContent)
FetchContent_Declare(
    CppUTest
    GIT_REPOSITORY https://github.com/cpputest/cpputest.git
    GIT_TAG v4.0
    GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(CppUTest)

add_subdirectory(../core core)

# Fakes subdirectories
add_subdirectory(fakes/transport) # -> provides transport_fake lib.

add_executable(zero_test
  src/rpc_test.cpp
  src/test_main.cpp
)

target_link_libraries(zero_test
  CppUTest
  CppUTestExt
  transport_fake
)
