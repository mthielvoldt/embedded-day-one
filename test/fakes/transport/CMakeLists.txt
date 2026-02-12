cmake_minimum_required(VERSION 3.25)

add_library(transport_fake
  transport_fake.cpp
)

target_link_libraries(transport_fake CppUTestExt core)

target_include_directories(transport_fake
  PUBLIC
    .
)
