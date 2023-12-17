/*
MIT License

Copyright (c) 2022 Sukesh Ashok Kumar

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef DISPLAY_CONFIG_HPP
#define DISPLAY_CONFIG_HPP


#include "lv_conf.h"
#include <lvgl.h>


#define LV_TICK_PERIOD_MS 1
    
/*********************
 *  THEME DEFINES
 *********************/
#define MODE_DARK 1
#define RADIUS_DEFAULT (disp_size == DISP_LARGE ? lv_disp_dpx(theme.disp, 12) : lv_disp_dpx(theme.disp, 8))

/*SCREEN*/
#define LIGHT_COLOR_SCR        lv_palette_lighten(LV_PALETTE_GREY, 4)
#define LIGHT_COLOR_CARD       lv_color_white()
#define LIGHT_COLOR_TEXT       lv_palette_darken(LV_PALETTE_GREY, 4)
#define LIGHT_COLOR_GREY       lv_palette_lighten(LV_PALETTE_GREY, 2)
#define DARK_COLOR_SCR         lv_color_hex(0x15171A)
#define DARK_COLOR_CARD        lv_color_hex(0x282b30)
#define DARK_COLOR_TEXT        lv_palette_lighten(LV_PALETTE_GREY, 5)
#define DARK_COLOR_GREY        lv_color_hex(0x2f3237)

#define TRANSITION_TIME         LV_THEME_DEFAULT_TRANSITION_TIME
#define BORDER_WIDTH            lv_disp_dpx(theme.disp, 2)
#define OUTLINE_WIDTH           lv_disp_dpx(theme.disp, 3)

#define PAD_DEF     (disp_size == DISP_LARGE ? lv_disp_dpx(theme.disp, 24) : disp_size == DISP_MEDIUM ? lv_disp_dpx(theme.disp, 20) : lv_disp_dpx(theme.disp, 16))
#define PAD_SMALL   (disp_size == DISP_LARGE ? lv_disp_dpx(theme.disp, 14) : disp_size == DISP_MEDIUM ? lv_disp_dpx(theme.disp, 12) : lv_disp_dpx(theme.disp, 10))
#define PAD_TINY   (disp_size == DISP_LARGE ? lv_disp_dpx(theme.disp, 8) : disp_size == DISP_MEDIUM ? lv_disp_dpx(theme.disp, 6) : lv_disp_dpx(theme.disp, 2))


/*** Setup screen resolution for LVGL ***/
static const uint16_t screenWidth = TFT_WIDTH;
static const uint16_t screenHeight = TFT_HEIGHT;

#define BUFF_SIZE 40
#define LVGL_DOUBLE_BUFFER

static lv_disp_draw_buf_t draw_buf;

static lv_disp_t *disp;
static lv_theme_t *theme_current;
static lv_color_t bg_theme_color;

static LGFX lcd; // declare display variable

/* Creates a semaphore to handle concurrent call to lvgl stuff
 * If you wish to call *any* lvgl function from other threads/tasks
 * you should lock on the very same semaphore! */
static SemaphoreHandle_t xGuiSemaphore = nullptr;
static TaskHandle_t g_lvgl_task_handle;

static void lvgl_task(void *args);

/*** Function declaration ***/
void display_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p);
void touchpad_read(lv_indev_drv_t *indev_driver, lv_indev_data_t *data);
static void lv_tick_task(void *arg);


esp_err_t lv_display_init();

// Display callback to flush the buffer to screen
void display_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p);

/* Setting up tick task for lvgl */
static void lv_tick_task(void *arg);

static void lvgl_task(void *args);

void lvgl_acquire();

void lvgl_release();

// Touchpad callback to read the touchpad
void touchpad_read(lv_indev_drv_t *indev_driver, lv_indev_data_t *data);

#endif // DISPLAY_CONFIG_HPP