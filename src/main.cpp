#include "FreeRTOS.h"
#include "task.h"
#include "pico/stdlib.h"
#include "sx1276.h"


LoRa Lora = LoRa(spi0, 16, 19, 18, 17, 20, 21);

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

int main()
{
    stdio_init_all();

    xTaskCreate(led_task, "LED_Task", 256, NULL, 1, NULL);
    vTaskStartScheduler();

    while(true){};
}