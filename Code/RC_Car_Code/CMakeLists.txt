cmake_minimum_required(VERSION 3.13)

set(PROGRAM_NAME car)
set(PICO_BOARD pico_w)

include(pico_sdk_import.cmake)

project(pico_hm01b0)

pico_sdk_init()

add_library(pico_hm01b0 INTERFACE)

message("Running makefsdata python script")
execute_process(COMMAND
    py makefsdata.py
    WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
)

add_executable(${PROGRAM_NAME}
    main.c
)

target_sources(pico_hm01b0 INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}/hm01b0.c
)

target_include_directories(pico_hm01b0 INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}
)

target_include_directories(${PROGRAM_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}
)

target_link_libraries(pico_hm01b0 INTERFACE
    cmsis_core
    hardware_dma
    hardware_i2c
    hardware_pio
    hardware_pwm
)

target_link_libraries(${PROGRAM_NAME} PRIVATE 
    pico_cyw43_arch_lwip_threadsafe_background
    pico_lwip_http
    pico_stdlib
    hardware_adc
    hardware_pwm
    pico_hm01b0
)

pico_enable_stdio_usb(${PROGRAM_NAME} 1)
pico_enable_stdio_uart(${PROGRAM_NAME} 0)

pico_add_extra_outputs(${PROGRAM_NAME})