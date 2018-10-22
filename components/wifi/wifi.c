/*
 * wifi.c
 *
 *  Created on: 23.07.2018
 *      Author: HummelZ
 */

#include <stdbool.h>

#include "esp_system.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_event_loop.h"
#include "nvs_flash.h"

#include "wifi.h"
#include "wifi_credentials.h"


static wifi_status_t  wifi_status;


static void wifi_init( void );
static void wifi_run( void );



esp_err_t event_handler( void *ctx, system_event_t *event ) {
  printf("Event received: %d\n", event->event_id);

  switch ( event->event_id ) {
    case SYSTEM_EVENT_STA_START:
      wifi_status = WIFI_STATUS_CONNECTING;
      ESP_ERROR_CHECK(esp_wifi_connect());
      break;

    case SYSTEM_EVENT_STA_CONNECTED:
      wifi_status = WIFI_STATUS_CONNECTING;
      break;

    case SYSTEM_EVENT_STA_DISCONNECTED:
      wifi_status = WIFI_STATUS_DISCONNECTED;
      printf("Reason: %d\n", event->event_info.disconnected.reason);
      ESP_ERROR_CHECK(esp_wifi_connect());
      break;

    case SYSTEM_EVENT_STA_GOT_IP:
      wifi_status = WIFI_STATUS_CONNECTED;
      break;

    case SYSTEM_EVENT_STA_LOST_IP:
      wifi_status = WIFI_STATUS_DISCONNECTED;
      break;

    default:
      break;
  }

  return ESP_OK;
}


static void wifi_init( void ) {
  wifi_status = WIFI_STATUS_NOT_INITIALIZED;

  // Initialize NVS
  esp_err_t ret = nvs_flash_init();
  if ( ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND ) {
    ESP_ERROR_CHECK(nvs_flash_erase());
    ret = nvs_flash_init();
  }
  ESP_ERROR_CHECK( ret );


  tcpip_adapter_init();
  ESP_ERROR_CHECK(esp_event_loop_init(event_handler, NULL));
  wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
  ESP_ERROR_CHECK(esp_wifi_init(&cfg));
  ESP_ERROR_CHECK(esp_wifi_set_storage(WIFI_STORAGE_RAM));
  wifi_config_t sta_config = {
    .sta = {
      .ssid = WIFI_SSID,
      .password = WIFI_KEY
    },
  };
  ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
  ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_STA, &sta_config));
  ESP_ERROR_CHECK(esp_wifi_start());

}


static void wifi_run( void ) {
  //if ( WIFI_STATUS_DISCONNECTED == wifi_status )
//    ESP_ERROR_CHECK(esp_wifi_start());
}


wifi_status_t wifi_getStatus( void ) {
  return wifi_status;
}


void wifi_task( void * pvParameters ) {
  wifi_init();
  while ( 1 ) {
    wifi_run();
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}
