/*
 * wifi.h
 *
 *  Created on: 23.07.2018
 *      Author: HummelZ
 */

#ifndef COMPONENTS_WIFI_WIFI_H_
#define COMPONENTS_WIFI_WIFI_H_


#ifdef __cplusplus
extern "C" {
#endif


typedef enum {
    WIFI_STATUS_NOT_INITIALIZED = 0
  , WIFI_STATUS_CONNECTING
  , WIFI_STATUS_CONNECTED
  , WIFI_STATUS_DISCONNECTED
} wifi_status_t;



/**
 * Returns the status of wifi
 *
 * @return  wifi_status_t   status of wifi
 */
wifi_status_t wifi_getStatus( void );



/**
 * Main task of wifi called by OS
 */
void wifi_task( void * pvParameters );


#ifdef __cplusplus
}
#endif
#endif /* COMPONENTS_WIFI_WIFI_H_ */
