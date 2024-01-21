#include "GUI.h"

void GUI_INIT()
{
    ESP_LOGE(COMPONENT_TAG_BOOT_GUI, "STARTING GUI");
    lcd.init();         // Initialize LovyanGFX
    lcd.initDMA();      // Init DMA
    lv_init();          // Initialize lvgl

    if (lv_display_init() != ESP_OK) // Configure LVGL
    {
        ESP_LOGE(COMPONENT_TAG_BOOT_GUI, "LVGL setup failed!!!");
    }
}
