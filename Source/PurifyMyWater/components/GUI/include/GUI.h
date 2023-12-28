#ifndef PURIFYMYWATER_GUI_H
#define PURIFYMYWATER_GUI_H

/******************** CORE LIBRARIES ********************/

#include "esp_log.h"

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

/******************** API *******************************/

void GUI_INIT();

/******************** API *******************************/

#endif //PURIFYMYWATER_GUI_H
