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
        blink.cpp
        )

# Allow  Usb Communication
pico_enable_stdio_usb(blink 1)
pico_enable_stdio_uart(blink 0)

# Pull in pico_stdlib
target_link_libraries(blink pico_stdlib)

# create map/bin/hex file etc.
pico_add_extra_outputs(blink)


