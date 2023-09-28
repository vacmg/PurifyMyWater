//
// Created by victor on 25/09/23.
//

#ifndef PURIFYMYWATER_MAIN_CONFIG_H
#define PURIFYMYWATER_MAIN_CONFIG_H


/******************** CORE LIBRARIES ********************/

#include <string>

#include "esp_log.h"

#include "esp_chip_info.h"
#include "esp_flash.h"
#include "esp_partition.h"
#include "esp_ota_ops.h"
#include "fmt/core.h"
#include "fmt/format.h"

using namespace std;
#include "soc/rtc.h"

#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"

/********************************************************/


/******************** DEVICE SELECTION ******************/

#if defined(CONFIG_DEVICE_WT32_SC01)
    /* Enable one of the devices from below (shift to bsp selection later) */
    #include "conf_WT32SCO1.h"              // WT32-SC01 (ESP32)
#elif defined(CONFIG_DEVICE_WT32_SC01_PLUS)
    // WT32-SC01 Plus (ESP32-S3 + 8Bit Parellel) with SD Card, Audio support
    #include "conf_WT32SCO1-Plus.h"
#else
    #error Unsupported device. Configure device in menuconfig
#endif

/********************************************************/


/******************** HARDWARE CONFIG *******************/

#include "display_config.hpp"


/********************************************************/


/******************** MODULE INCLUDES *******************/

/********************************************************/

#endif //PURIFYMYWATER_MAIN_CONFIG_H
