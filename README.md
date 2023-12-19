# ESP32-2432S028 Internet Synced (NTP) Clock

<p align="center">
  <img src="./img/image.jpg" width="400"/>
</p>

## Introduction

I wanted an NTP clock with time zones and automatic daylight savings time.  ESP32 has WiFi.  I found ESP32-2432S028 with a display attached.  You can buy it for under $10 in China, but I paid under $20 in the US so I wouldn't have to wait for shipping.

## Build

These instructions have been tested with Ubuntu 22.04.3 and Ardino IDE 2.0.2.

- brltty is an app for blind people, but it interferes with ESP32-2432S028 and must be removed.

    `sudo apt purge brltty`

- Arduino IDE requires pyserial

    `pip install pyserial`

- **Start Arduino IDE**
- **Select Board**

    Board is `ESP32 Dev Module`

    Port is `/dev/ttyUSB0`

    IDE will ask if you want to download and install esp32

- **Required libraries** · Use `Manage Libraries...` to install the `LovyanGFX` and `lvgl` libraries.
- **Clone repository**

    `cd ~/Arduino/`

    `git clone https://github.com/alannishioka/esp32-2432s028-clock.git`

- Copy `lv_conf.h` to `~/Arduino/libraries/`. This assumes `lvgl` library is in `~/Arduino/libraries/lvgl/`.
- Edit `config.h` to input your WiFi ssid/password.

- Connect ESP32-2432S028 to your computer with micro USB cable.

Build and install using Arduino IDE

## Notes

- Fonts were converted with [LVGL Online Font Convertor](https://lvgl.io/tools/fontconverter)
I used condensed because display is taller than it needs to be and so date would fit on a single line.

## Thank you

- This project is a fork of https://github.com/cjgb/esp32-2432s028-meteo
I feel it is fastest to get a project working by starting with something that already works!
- [NTP with Day Light Saving Time for the ESP32](https://werner.rothschopf.net/microcontroller/202103_arduino_esp32_ntp_en.htm) also explains how to change the NTP update interval.
- [Sunton ESP32 2.8 inch 240*320 TFT with Touch](https://wiki.makerfabs.com/Sunton_ESP32_2.8_inch_240x320_TFT_with_Touch.html)

