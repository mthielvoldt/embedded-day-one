cmake_minimum_required(VERSION 3.25.0)


set(PICO_SDK_PATH ${CMAKE_CURRENT_LIST_DIR}/deps/pico-sdk)
set(PICO_TOOLCHAIN_PATH ${CMAKE_CURRENT_LIST_DIR}/tools/arm-gnu-toolchain/bin)
include(deps/pico-sdk/external/pico_sdk_import.cmake)

project(test_project C CXX ASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

add_executable(test
  src/main.c
)

# pico_enable_stdio_usb(test 1)
# pico_enable_stdio_uart(test 1)
pico_add_extra_outputs(test)

target_link_libraries(test pico_stdlib)