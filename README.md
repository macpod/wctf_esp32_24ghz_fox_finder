# WCTF ESP32 2.4Ghz AP Fox Finder
This Arduino project turns a TTGO ESP32 module with OLED display and 18650 battery holder into a a cheap/small/simple 2.4Ghz WiFi AP Fox Hunter.
The OLED display shows:
* The number of APs seen
* A rectangle which will toggle on/off each time a scan has been refreshed
* The RSSI of the designated BSSID and SSID at the top of the sketch. 

This was a last-minute Quick n' Dirty® project made so a few friends would have *something* to try to hone in on a fox if they didn't bring any equipment. **There are many improvements that could be made to this!** 


## General Notes
* This is 2.4Ghz only! The tracked fox this year was on 5Ghz which made this rather useless outside the inadvertent excercise side effect
* This code is likely to freeze/behave poorly if there are lots of wifi shenenigans happening
* This was left on for several hours without dying
* This module could perform bluetooth LE scans 
* The 2nd revision ESP32 modules allegedly have better wireless performance. This module uses the 1st rev chip
* It might be nice to find an ESP32 module for this board with a U.FL connector in order to use a directional antenna or to allow adding of some attenuators.


## Setting up the Arduino IDE
1. Install the current upstream Arduino IDE at the 1.8 level or later. The current version is at the Arduino website.
2. Start Arduino and open Preferences window.
3. Enter http://dl.espressif.com/dl/package_esp32_index.json into Additional Board Manager URLs field. You can add multiple URLs, separating them with commas.
4. Open Boards Manager from Tools > Board menu and install esp32 platform (and don't forget to select your ESP32 board from Tools > Board menu after installation).
5. Open Manage Libraries from Sketch->Include Library
6. Search for and install the "ESP8266 and ESP32 Oled Driver for SSD1306 dispay" library from https://github.com/ThingPulse/esp8266-oled-ssd1306 

## Board configuration:
* Board: "WeMos WiFi&Bluetooth Battery"
* Upload Speed: "921600"
* Flash Frequency: "80Mhz"
* Core Debug Level: "None"

## Resources
* I found this blog post helpful in identifying the pins for this board:
  * http://www.areresearch.net/2018/01/how-to-use-ttgo-esp32-module-with-oled.html
* This code started from this sketch:
  * https://github.com/djpm05/TTGO_esp32_oled_battery_18650-wifi-scanner




Enjoy!  
[@macpod](https://twitter.com/macpoddotnet)  
https://macpod.net


