cmake_minimum_required(VERSION 3.13)

include("$ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake")

project(pico_con_example C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
pico_sdk_init()

include("pico-con/pico-con.cmake")

add_executable(pico_con_example
	main.c
)

if(BATCH)
	target_compile_definitions(pico_con_example PRIVATE BATCH)
endif(BATCH)

add_compile_definitions(
  $<$<CONFIG:Debug>:DEBUG>
)

pico_enable_stdio_usb(pico_con_example 1)
pico_enable_stdio_uart(pico_con_example 0)

pico_add_extra_outputs(pico_con_example)

target_link_libraries(pico_con_example pico_stdlib pico_con)
