add_library(Telemetry INTERFACE)

target_include_directories(Telemetry INTERFACE ./include)

target_link_libraries(Telemetry INTERFACE
        GPS
        ICM20948
        BME280
)
