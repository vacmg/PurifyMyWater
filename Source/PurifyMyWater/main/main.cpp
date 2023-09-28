/**
 *
 */

static const char* INIT_COMPONENT_TAG = "PurifyMyWater - Init";

#include "main_config.h"

#include "deviceInfo.h"


/**
 * App entry point
 */
extern "C" void app_main(void)
{
    esp_log_level_set(INIT_COMPONENT_TAG,ESP_LOG_DEBUG);

    ESP_LOGE(INIT_COMPONENT_TAG,"\n%s",device_info().c_str());


    lcd.init();         // Initialize LovyanGFX
    lcd.initDMA();      // Init DMA
    lv_init();          // Initialize lvgl

    if (lv_display_init() != ESP_OK) // Configure LVGL
    {
        ESP_LOGE(INIT_COMPONENT_TAG, "LVGL setup failed!!!");
    }



    vTaskSuspend(nullptr);
}
