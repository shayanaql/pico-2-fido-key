add_executable(fidokey main.c blink.c)
target_include_directories(fidokey PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}/include
)
target_link_libraries(fidokey pico_stdlib)
pico_enable_stdio_uart(fidokey 1)
pico_enable_stdio_usb(fidokey 0)
pico_add_extra_outputs(fidokey)

