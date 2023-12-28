#ifndef PURIFYMYWATER_DEVICEINFO_H
#define PURIFYMYWATER_DEVICEINFO_H

#include <string>
#include "fmt/format.h"

#include "esp_chip_info.h"
#include "esp_flash.h"
#include "esp_ota_ops.h"
#include "soc/rtc.h"
#include "freertos/FreeRTOS.h"

std::string device_info();

#endif //PURIFYMYWATER_DEVICEINFO_H