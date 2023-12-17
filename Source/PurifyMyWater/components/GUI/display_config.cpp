//
// Created by victor on 17/12/23.
//

#include "GUI.h"
#include "display_config.hpp"

esp_err_t lv_display_init()
{
    // Setting display to landscape
    // if (lcd.width() < lcd.height()) lcd.setRotation(lcd.getRotation() ^ 2);

    lcd.setRotation(2);
    lcd.setColorDepth(16);
    lcd.setBrightness(128);
    //lcd.fillScreen(TFT_BLACK);

    /* LVGL : Setting up buffer to use for display */
#if defined(LVGL_DOUBLE_BUFFER)
    // EXT_RAM_BSS_ATTR lv_color_t * buf1 = (lv_color_t *)malloc(screenWidth * BUFF_SIZE * sizeof(lv_color_t));
    // EXT_RAM_BSS_ATTR lv_color_t * buf2 = (lv_color_t *)malloc(screenWidth * BUFF_SIZE * sizeof(lv_color_t));

    auto * buf1 = (lv_color_t *)heap_caps_malloc(screenWidth * BUFF_SIZE * sizeof(lv_color_t),MALLOC_CAP_DMA);
    auto * buf2 = (lv_color_t *)heap_caps_malloc(screenWidth * BUFF_SIZE * sizeof(lv_color_t),MALLOC_CAP_DMA);

    lv_disp_draw_buf_init(&draw_buf, buf1, buf2, screenWidth * BUFF_SIZE);
#else
    // EXT_RAM_BSS_ATTR lv_color_t * buf1 = (lv_color_t *)malloc(screenWidth * BUFF_SIZE * sizeof(lv_color_t));
    lv_color_t * buf1 = (lv_color_t *)heap_caps_malloc(screenWidth * BUFF_SIZE * sizeof(lv_color_t),MALLOC_CAP_DMA);
    lv_disp_draw_buf_init(&draw_buf, buf1, NULL, screenWidth * BUFF_SIZE);
#endif

    /*** LVGL : Setup & Initialize the display device driver ***/
    static lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);
    disp_drv.hor_res = screenWidth;
    disp_drv.ver_res = screenHeight;
    disp_drv.flush_cb = display_flush;
    disp_drv.draw_buf = &draw_buf;
    disp_drv.sw_rotate = 1;
    disp = lv_disp_drv_register(&disp_drv);

    //*** LVGL : Setup & Initialize the input device driver ***
    static lv_indev_drv_t indev_drv;
    lv_indev_drv_init(&indev_drv);
    indev_drv.type = LV_INDEV_TYPE_POINTER;
    indev_drv.read_cb = touchpad_read;
    lv_indev_drv_register(&indev_drv);

    /* Create and start a periodic timer interrupt to call lv_tick_inc */
    const esp_timer_create_args_t lv_periodic_timer_args = {
            .callback = &lv_tick_task,
            .arg = nullptr,
            .dispatch_method = ESP_TIMER_TASK,
            .name = "periodic_gui",
            .skip_unhandled_events  = true
    };
    esp_timer_handle_t lv_periodic_timer;
    ESP_ERROR_CHECK(esp_timer_create(&lv_periodic_timer_args, &lv_periodic_timer));
    ESP_ERROR_CHECK(esp_timer_start_periodic(lv_periodic_timer, LV_TICK_PERIOD_MS * 1000));

    // Setup theme
    theme_current = lv_theme_default_init(disp, lv_palette_main(LV_PALETTE_BLUE),
                                          lv_palette_main(LV_PALETTE_RED),
                                          LV_USE_THEME_DEFAULT, /*Light or dark mode*/
                                          &lv_font_montserrat_14);

    //lv_disp_set_theme(disp, theme_current); /*Assign the theme to the display*/
    //bg_theme_color = theme_current->flags & LV_USE_THEME_DEFAULT ? DARK_COLOR_CARD : LIGHT_COLOR_CARD;
    bg_theme_color = theme_current->flags & LV_USE_THEME_DEFAULT ? lv_palette_darken(LV_PALETTE_GREY, 5) : lv_color_hex(0xBFBFBD);

    xGuiSemaphore = xSemaphoreCreateMutex();
    if (!xGuiSemaphore)
    {
        ESP_LOGE(BOOT_GUI_COMPONENT_TAG, "Create mutex for LVGL failed");
        if (lv_periodic_timer) esp_timer_delete(lv_periodic_timer);
        return ESP_FAIL;
    }

#if CONFIG_FREERTOS_UNICORE == 0
    int err = xTaskCreatePinnedToCore(lvgl_task, "LVGL Task", 1024 * 8, nullptr, 3, &g_lvgl_task_handle, APP_CPU_NUM);
#else
    int err = xTaskCreatePinnedToCore(lvgl_task, "LVGL Task", 1024 * 8, NULL, 3, &g_lvgl_task_handle, PRO_CPU_NUM;
#endif
    if (!err)
    {
        ESP_LOGE(BOOT_GUI_COMPONENT_TAG, "Create task for LVGL failed");
        if (lv_periodic_timer) esp_timer_delete(lv_periodic_timer);
        return ESP_FAIL;
    }

    return ESP_OK;
}

// Display callback to flush the buffer to screen
void display_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p)
{
    int32_t w = (area->x2 - area->x1 + 1);
    int32_t h = (area->y2 - area->y1 + 1);

    /* Without DMA */
    // lcd.startWrite();
    // lcd.setAddrWindow(area->x1, area->y1, w, h);
    // lcd.pushPixels((uint16_t *)&color_p->full, w * h, true);
    // lcd.endWrite();

    /* With DMA */
    // TODO: Yet to do performance test
    lcd.startWrite();
    lcd.setAddrWindow(area->x1, area->y1, w, h);
    lcd.pushImageDMA(area->x1, area->y1, area->x2 - area->x1 + 1, area->y2 - area->y1 + 1, (lgfx::swap565_t *)&color_p->full);
    lcd.endWrite();

    lv_disp_flush_ready(disp);
}

/* Setting up tick task for lvgl */
static void lv_tick_task(void *arg)
{
    (void)arg;
    lv_tick_inc(LV_TICK_PERIOD_MS);
}

static void lvgl_task(void *args)
{
    ESP_LOGI(BOOT_GUI_COMPONENT_TAG, "Start to run LVGL");
    while (1)
    {
        vTaskDelay(pdMS_TO_TICKS(10));

        /* Try to take the semaphore, call lvgl related function on success */
        if (pdTRUE == xSemaphoreTake(xGuiSemaphore, portMAX_DELAY)) {
            lv_task_handler();
            //lv_timer_handler_run_in_period(5); /* run lv_timer_handler() every 5ms */
            xSemaphoreGive(xGuiSemaphore);
        }
    }
}

void lvgl_acquire()
{
    TaskHandle_t task = xTaskGetCurrentTaskHandle();
    if (g_lvgl_task_handle != task) {
        xSemaphoreTake(xGuiSemaphore, portMAX_DELAY);
    }
}

void lvgl_release()
{
    TaskHandle_t task = xTaskGetCurrentTaskHandle();
    if (g_lvgl_task_handle != task) {
        xSemaphoreGive(xGuiSemaphore);
    }
}

// Touchpad callback to read the touchpad
void touchpad_read(lv_indev_drv_t *indev_driver, lv_indev_data_t *data)
{
    int16_t touchX, touchY;
    bool touched = lcd.getTouch(&touchX, &touchY);

    if (!touched)
    {
        data->state = LV_INDEV_STATE_REL;
    }
    else
    {
        data->state = LV_INDEV_STATE_PR;

        // Set the coordinates
        data->point.x = touchX;
        data->point.y = touchY;
    }
}
