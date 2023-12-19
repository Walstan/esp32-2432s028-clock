/////////////////////////////////////////////////////////////////
/*
@gilbellosta, 2023-04-09
Adapted from https://docs.lvgl.io/master/widgets/chart.html
*/
/////////////////////////////////////////////////////////////////

#include <stdlib.h>

#define LGFX_USE_V1
#include <LovyanGFX.hpp>
#include "lgfx_ESP32_2432S028.h"
#include <lvgl.h>

#include <WiFi.h>

#include "esp_sntp.h"
#include "time.h"
#include "config.h"


/* Change to your screen resolution */
static const uint32_t screenWidth  = 320;
static const uint32_t screenHeight = 240;

static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf[ screenWidth * 10 ];

lv_obj_t *screenMain;

lv_obj_t *label1;
lv_obj_t *label2;
lv_obj_t *label3;

void setTimezone(String timezone)
{
  Serial.printf("Setting Timezone to %s\n",timezone.c_str());
  setenv("TZ",timezone.c_str(),1);  //  Now adjust the TZ.  Clock settings are adjusted to show the new local time
  tzset();
}

// callback function to show when NTP was synchronized
void cbSyncTime(struct timeval *tv)
{
  Serial.println(F("NTP time synched"));
  printLocalTime();
}

// /* Display flushing */
void my_disp_flush( lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p )
{
   uint32_t w = ( area->x2 - area->x1 + 1 );
   uint32_t h = ( area->y2 - area->y1 + 1 );

   tft.startWrite();
   tft.setAddrWindow( area->x1, area->y1, w, h );
   tft.writePixels((lgfx::rgb565_t *)&color_p->full, w * h);
   tft.endWrite();

   lv_disp_flush_ready( disp );
}

void setup()
{
    Serial.begin(115200);

    WiFi.begin(SSID, wifi_password);
    while (WiFi.status() != WL_CONNECTED)
    {
      delay(1000);
      Serial.println("Connecting to WiFi...");
    }
    Serial.println("Connected to WiFi");

    // Init and get the time
    sntp_set_sync_interval(12 * 60 * 60 * 1000UL); // 12 hours
    sntp_set_time_sync_notification_cb(cbSyncTime);  // set a Callback function for time synchronization notification
    configTime(0, 0, ntpServer);

    setTimezone(timezone);

    printLocalTime();

    tft.begin();
    tft.setRotation(1);
    tft.setBrightness(32);
    // uint16_t calData[] = {3749, 3619, 3737, 207, 361, 3595, 267, 221};
    // tft.setTouchCalibrate(calData);

    lv_init();
    lv_disp_draw_buf_init( &draw_buf, buf, NULL, screenWidth * 10 );

    /*Initialize the display*/
    static lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);

    /*Change the following line to your display resolution*/
    disp_drv.hor_res = screenWidth;
    disp_drv.ver_res = screenHeight;
    disp_drv.flush_cb = my_disp_flush;
    disp_drv.draw_buf = &draw_buf;
    lv_disp_drv_register(&disp_drv);

    screenMain = lv_obj_create(NULL);
    lv_obj_set_style_bg_color(screenMain, lv_color_black(), LV_PART_MAIN);

    LV_FONT_DECLARE(opensans_30);
    LV_FONT_DECLARE(opensans_90);

    static lv_style_t style_font1;
    lv_style_init(&style_font1);
    lv_style_set_text_font(&style_font1, &opensans_30);

    static lv_style_t style_font2;
    lv_style_init(&style_font2);
    lv_style_set_text_font(&style_font2, &opensans_90);

    label1 = lv_label_create(screenMain);
    lv_obj_add_style(label1, &style_font1, 0);
    lv_obj_set_style_text_align(label1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);
    lv_obj_set_style_text_color(label1, lv_color_hex(0xffffff), LV_PART_MAIN);
    lv_obj_set_size(label1, 320, 30);
    lv_obj_set_pos(label1, 0, 0);

    label2 = lv_label_create(screenMain);
    lv_obj_add_style(label2, &style_font2, 0);
    lv_obj_set_style_text_align(label2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);
    lv_obj_set_style_text_color(label2, lv_color_hex(0xffffff), LV_PART_MAIN);
    lv_obj_set_size(label2, 320, 80);
    lv_obj_set_pos(label2, 0, (240-80)/2);

    label3 = lv_label_create(screenMain);
    lv_label_set_text(label3, timezone_text);
    lv_obj_add_style(label3, &style_font1, 0);
    lv_obj_set_style_text_align(label3, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);
    lv_obj_set_style_text_color(label3, lv_color_hex(0xffffff), LV_PART_MAIN);
    lv_obj_set_size(label3, 320, 30);
    lv_obj_set_pos(label3, 0, 240-30);

    lv_scr_load(screenMain);

    Serial.println("Setup ended!");
}

void loop()
{
    lv_timer_handler(); /* let the GUI do its work */

    update_labels();
}

void update_labels()
{
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo))
  {
    Serial.println("Failed to obtain time");
    return;
  }

  char current_date[64];
  strftime( current_date, 64, "%A, %B %d %Y", &timeinfo );
  lv_label_set_text(label1, current_date);

  char current_time[64];
  strftime( current_time, 64, time_format, &timeinfo );
  lv_label_set_text(label2, current_time);
}

void printLocalTime()
{
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo))
  {
    Serial.println("Failed to obtain time");
  }
  else
  {
    Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S zone %Z %z");
  }
}
