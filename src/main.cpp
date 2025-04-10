#include <Arduino.h>
#include <lvgl.h>
#include <LovyanGFX.hpp>
#include "Elecrow_ESP32_7.hpp"
LGFX lcd;


static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf[800 * 20];

void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p) {
  lcd.startWrite();
  lcd.setAddrWindow(area->x1, area->y1, area->x2, area->y2);
  lcd.writePixels((lgfx::rgb565_t *)&color_p->full, (area->x2 - area->x1 + 1) * (area->y2 - area->y1 + 1));
  lcd.endWrite();
  lv_disp_flush_ready(disp);
}

void setup() {
  Serial.begin(115200);
  lcd.init();
  lcd.setBrightness(255);
  lv_init();

  lv_disp_draw_buf_init(&draw_buf, buf, NULL, 800 * 20);
  static lv_disp_drv_t disp_drv;
  lv_disp_drv_init(&disp_drv);
  disp_drv.flush_cb = my_disp_flush;
  disp_drv.draw_buf = &draw_buf;
  disp_drv.hor_res = 800;
  disp_drv.ver_res = 480;
  lv_disp_drv_register(&disp_drv);

  lv_obj_t *label = lv_label_create(lv_scr_act());
  lv_label_set_text(label, "AgriControlPlus");
  lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);
}

void loop() {
  lv_timer_handler();
  delay(5);
}