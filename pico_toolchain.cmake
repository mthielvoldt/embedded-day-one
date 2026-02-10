set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)

set(arm_toolchain_path ${CMAKE_CURRENT_LIST_DIR}/tools/arm-gnu-toolchain)
set(CMAKE_C_COMPILER   ${arm_toolchain_path}/bin/arm-none-eabi-gcc)
set(CMAKE_CXX_COMPILER ${arm_toolchain_path}/bin/arm-none-eabi-g++)
set(CMAKE_C_OBJCOPY    ${arm_toolchain_path}/bin/arm-none-eabi-objcopy)

set(CMAKE_C_FLAGS "-mcpu=cortex-m0plus -mthumb")

# Suppresses the check for a working compiler, which will fail for sys calls since there's no sys.
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)