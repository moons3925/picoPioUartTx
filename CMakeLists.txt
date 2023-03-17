# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Initialise pico_sdk from installed location
# (note this can come from environment, CMake cache etc)
set(PICO_SDK_PATH "C:/Users/m3925/Documents/Pico/pico-sdk")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(picoPioUartTx C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add executable. Default name is the project name, version 0.1

add_executable(picoPioUartTx picoPioUartTx.c )

#この１行を追加
pico_generate_pio_header(picoPioUartTx ${CMAKE_CURRENT_LIST_DIR}/picoPioUartTx.pio)

pico_set_program_name(picoPioUartTx "picoPioUartTx")
pico_set_program_version(picoPioUartTx "0.1")

pico_enable_stdio_uart(picoPioUartTx 0)
pico_enable_stdio_usb(picoPioUartTx 0)

# Add the standard library to the build
target_link_libraries(picoPioUartTx pico_stdlib)

# Add any user requested libraries
target_link_libraries(picoPioUartTx
        hardware_pio
        )

pico_add_extra_outputs(picoPioUartTx)

