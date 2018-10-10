/*
 * wifi.h
 *
 *  Created on: 23.07.2018
 *      Author: HummelZ
 */

#ifndef COMPONENTS_WIFI_WIFI_H_
#define COMPONENTS_WIFI_WIFI_H_

#include <stdbool.h>

#include "esp_system.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_event_loop.h"
#include "nvs_flash.h"

#ifdef __cplusplus
extern "C" {
#endif


void wifi_task( void * pvParameters );


#ifdef __cplusplus
}
#endif
#endif /* COMPONENTS_WIFI_WIFI_H_ */
