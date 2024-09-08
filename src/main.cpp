#include "FreeRTOS.h"
#include "task.h"
#include "pico/stdlib.h"
#include <cstdio>

#include "m100Mini.h"


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

void gps_task(void*){
  GPS::NAV_POSLLH navData;
  while(true){
    if(m100Mini.GetGPS(&navData)){
      printf("Lat: %ld, Lon: %ld\n", navData.lat, navData.lon);
    }else{
      printf("wait gps\n");
    }
    vTaskDelay(50 / portTICK_PERIOD_MS);
  }
}

int main()
{
    stdio_init_all();

    m100Mini.m100Mini_Init();

    xTaskCreate(gps_task, "GPS_task", 256, NULL, 1, NULL);
    xTaskCreate(led_task, "LED_task", 256, NULL, 2, NULL);
    vTaskStartScheduler();

    while(true){};
}