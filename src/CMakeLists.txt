
add_executable(${ProjectName}
    main.cpp
)

target_include_directories(${ProjectName} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}
)

target_link_libraries(${ProjectName}
        pico_stdlib
        FreeRTOS-Kernel-Heap4
        SX1276
        GPS
        BME280
        ICM20948
        Telemetry
    )

pico_add_extra_outputs(${ProjectName})