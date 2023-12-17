/**
 *
 */

static const char* BOOT_COMPONENT_TAG = "PurifyMyWater - Boot";

#include "main_config.h"

#include "deviceInfo.h"


/**
 * App entry point
 */
extern "C" void app_main(void)
{
    esp_log_level_set(BOOT_COMPONENT_TAG,ESP_LOG_DEBUG);

    ESP_LOGE(BOOT_COMPONENT_TAG,"\n%s",device_info().c_str());

    vTaskSuspend(nullptr);
}
