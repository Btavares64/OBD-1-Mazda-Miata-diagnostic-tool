cmake_minimum_required(VERSION 3.13)

set(PICO_SDK_PATH "${CMAKE_CURRENT_LIST_DIR}/../pico-sdk")

# Pull in PICO SDK 
include("${PICO_SDK_PATH}/pico_sdk_init.cmake")

# Initilize the SDK
pico_sdk_init()

project(blink C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

add_executable(blink
        blink.c
        )

# Collect FreeRTOS source files
file(GLOB FreeRTOS_src
    ../FreeRTOS-Kernel/*.c
    ../FreeRTOS-Kernel/portable/GCC/ARM_CM0/port.c
    ../FreeRTOS-Kernel/portable/MemMang/heap_4.c
)

# Create static library for FreeRTOS
add_library(FreeRTOS STATIC ${FreeRTOS_src})

# Include FreeRTOS headers
target_include_directories(FreeRTOS PUBLIC
    ../FreeRTOS-Kernel/include
    ../FreeRTOS-Kernel/portable/GCC/ARM_CM0
)

# Allow  Usb Communication
pico_enable_stdio_usb(blink 1)
pico_enable_stdio_uart(blink 0)

# Pull in pico_stdlib
target_link_libraries(blink pico_stdlib)

# create map/bin/hex file etc.
pico_add_extra_outputs(blink)


