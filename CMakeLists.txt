cmake_minimum_required(VERSION 3.28)

cmake_policy(SET CMP0076 NEW)

set(ProjectName CanSAT)

set(FREERTOS_KERNEL_PATH ${CMAKE_CURRENT_SOURCE_DIR}/lib/FreeRTOS-Kernel)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG")


include(pico_sdk_import.cmake)
include(${FREERTOS_KERNEL_PATH}/portable/ThirdParty/GCC/RP2040/FreeRTOS_Kernel_import.cmake)

project(${ProjectName} C CXX ASM)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 11)

pico_sdk_init()

add_subdirectory(src)
add_subdirectory(lib)

pico_enable_stdio_usb(CanSAT 1)
pico_enable_stdio_uart(CanSAT 0)