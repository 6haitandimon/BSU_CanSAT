add_library(GPS INTERFACE)

target_include_directories(GPS INTERFACE ./include)

target_sources(GPS
        INTERFACE
        m100Mini.cpp
)

target_link_libraries(GPS
        INTERFACE
        pico_stdlib
        hardware_uart
        hardware_irq
)
