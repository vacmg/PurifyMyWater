#include "PrivGUI.h"

void GUI_INIT()
{
    ESP_LOGE(BOOT_GUI_COMPONENT_TAG, "STARTING GUI");
    lcd.init();         // Initialize LovyanGFX
    lcd.initDMA();      // Init DMA
    lv_init();          // Initialize lvgl

    if (lv_display_init() != ESP_OK) // Configure LVGL
    {
        ESP_LOGE(BOOT_GUI_COMPONENT_TAG, "LVGL setup failed!!!");
    }
}
