#include "FreeRTOS.h"
#include "task.h"
#include "pico/stdlib.h"
#include <cstdio>

#include "m100Mini.h"
#include "BME280.h"
#include "ICM20948.h"
#include "Telemetry.h"

Telemetry telemetry;


ICM::ICM20948 icm20948 = ICM::ICM20948(i2c0, 4, 5, 0x68);
GPS::M100Mini m100Mini = GPS::M100Mini(uart1, 8, 9, 115200);

void led_task(void*)
{
    const uint LED_PIN = PICO_DEFAULT_LED_PIN;
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    while (true) {
        gpio_put(LED_PIN, true);
        vTaskDelay(100);
        gpio_put(LED_PIN, false);
        vTaskDelay(100);
    }
}

void print_terminal(void*){
  while(true){
    printf("GPS\nLat: %ld, Lon: %ld\n\n", telemetry.gpsData.lat, telemetry.gpsData.lon);
    printf("ICM Accel Data\n x: %f, y: %f, z:%f\n\n", telemetry.icm20948Data.Accsel_x, telemetry.icm20948Data.Accsel_y, telemetry.icm20948Data.Accsel_z);
    vTaskDelay(50 / portTICK_PERIOD_MS);
  }
}

void gps_task(void*){
  while(true){
    if(m100Mini.GetGPS(&telemetry.gpsData));

    vTaskDelay(50 / portTICK_PERIOD_MS);
  }
}

void icm_task(void*){
  while (true) {
    icm20948.getAllData(&telemetry.icm20948Data);

    vTaskDelay(50 / portTICK_PERIOD_MS);
  }
}


int main()
{
    stdio_init_all();

    gpio_init(2);

    gpio_put(2, false);
    gpio_put(2, true);

    m100Mini.m100Mini_Init();
    icm20948.init();

    xTaskCreate(gps_task, "GPS_task", 256, NULL, 2, NULL);
    xTaskCreate(icm_task, "ICM_task", 256, NULL, 2, NULL);
    xTaskCreate(led_task, "LED_task", 256, NULL, 1, NULL);
    xTaskCreate(print_terminal, "TerminalPC", 256, NULL, 1, NULL);

    vTaskStartScheduler();

    while(true){};
}