cmake_minimum_required(VERSION 3.25)

add_library(serial
  serial_fake.cpp
)

target_link_libraries(serial CppUTestExt)

target_include_directories(serial
  PUBLIC
    .
)
