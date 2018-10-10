/*
 * wifi.c
 *
 *  Created on: 23.07.2018
 *      Author: HummelZ
 */


#include "wifi.h"
#include "wifi_credentials.h"


static void wifi_init( void );
static void wifi_run( void );



esp_err_t event_handler(void *ctx, system_event_t *event)
{
	printf("Event received: %d\n", event->event_id );

	switch ( event->event_id )
	{
	case SYSTEM_EVENT_STA_START:
		ESP_ERROR_CHECK( esp_wifi_connect() );
		break;

	case SYSTEM_EVENT_STA_CONNECTED:
		break;

	case SYSTEM_EVENT_STA_DISCONNECTED:
		break;


	case SYSTEM_EVENT_STA_GOT_IP:
		break;

	case SYSTEM_EVENT_STA_LOST_IP:
		break;

	default:
		break;

	}

	return ESP_OK;

}


static void wifi_init( void )
{
	nvs_flash_init();
	tcpip_adapter_init();
	ESP_ERROR_CHECK( esp_event_loop_init(event_handler, NULL) );
	wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
	ESP_ERROR_CHECK( esp_wifi_init(&cfg) );
	ESP_ERROR_CHECK( esp_wifi_set_storage(WIFI_STORAGE_RAM) );
	ESP_ERROR_CHECK( esp_wifi_set_mode(WIFI_MODE_STA) );
	wifi_config_t sta_config = {
		.sta = {
			.ssid = WIFI_SSID,
			.password = WIFI_KEY,
			.bssid_set = false
		}
	};
	ESP_ERROR_CHECK( esp_wifi_set_config(WIFI_IF_STA, &sta_config) );
	ESP_ERROR_CHECK( esp_wifi_start() );

}



static void wifi_run( void )
{

}


void wifi_task( void * pvParameters )
{
	wifi_init();
	while ( 1 )
	{
		wifi_run();
		vTaskDelay(1000 / portTICK_PERIOD_MS);
	}
}
