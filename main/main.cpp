/* Hello World Example

 This example code is in the Public Domain (or CC0 licensed, at your option.)

 Unless required by applicable law or agreed to in writing, this
 software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
 CONDITIONS OF ANY KIND, either express or implied.
 */
#include <stdio.h>
#include <stdbool.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
//#include "esp_spi_flash.h"


#include "i2c.h"
#include "sensor.h"
#include "wifi.h"


extern "C" void app_main() {
  int i = 0;

  /* Initialization of components */
  i2c_init();

  /* Task creation */
  xTaskCreate(sensor_task, "sensor", 5000, NULL, 10, NULL);
  xTaskCreate(wifi_task, "wifi", 5000, NULL, 5, NULL);

  //Blynk.begin();

  /* let's go */
  while ( 1 ) {
    i++;
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
  return;

//    printf("Hello world!\n");
//
//    /* Print chip information */
//    esp_chip_info_t chip_info;
//    esp_chip_info(&chip_info);
//    printf("This is ESP32 chip with %d CPU cores, WiFi%s%s, ",
//            chip_info.cores,
//            (chip_info.features & CHIP_FEATURE_BT) ? "/BT" : "",
//            (chip_info.features & CHIP_FEATURE_BLE) ? "/BLE" : "");
//
//    printf("silicon revision %d, ", chip_info.revision);
//
//    printf("%dMB %s flash\n", spi_flash_get_chip_size() / (1024 * 1024),
//            (chip_info.features & CHIP_FEATURE_EMB_FLASH) ? "embedded" : "external");
//
//    for (int i = 50; i >= 0; i--) {
//        printf("Restarting in %d seconds...\n", i);
//        vTaskDelay(1000 / portTICK_PERIOD_MS);
//    }
//    printf("Restarting now.\n");
//    fflush(stdout);
//    esp_restart();
}
