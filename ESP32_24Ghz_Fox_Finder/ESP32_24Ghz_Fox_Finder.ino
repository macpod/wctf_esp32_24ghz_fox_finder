/*
    Quick and dirty TTGO ESP32 modile with OLED display and 18650 Battery holder WCTF 2.4Ghz AP Fox hunter. Use at your own risk
*/
#include "WiFi.h"
#include <SSD1306.h>
#include <Wire.h>
#include "images.h"

String FOX_BSSID = "D2:E4:0B:EA:C8:61";
String FOX_SSID = "xfinitywifi";

#define LED_PIN 16

#define OLED_ADDR 0x3C
#define OLED_SDA  5
#define OLED_SCL  4

SSD1306 display(OLED_ADDR, OLED_SDA, OLED_SCL);

void setup()
{
  Serial.begin(115200);

  pinMode (LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, HIGH);


  // Set WiFi to station mode and disconnect from an AP if it was previously connected
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
  display.init();
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.setFont(ArialMT_Plain_16);
  display.drawXbm(34, 0, WiFi_Logo_width, WiFi_Logo_height, (const uint8_t*)WiFi_Logo_bits);
  display.drawString(34, 40, "Scanner");
  display.display();

  display.setFont(ArialMT_Plain_10);
}

void draw_measurements(int yoff, int32_t rssi_max, int32_t rssi_avg, int32_t rssi_min)
{
  display.drawString(0, yoff * 10, String("Max: ") + rssi_max);
  display.drawString(42, yoff * 10, String("Avg: ") + rssi_avg);
  display.drawString(84, yoff * 10, String("Min: ") + rssi_min);
}

bool set = false;

int32_t bssid_rssi_min = 0;
int32_t bssid_rssi_max = 0;
int32_t bssid_rssi_avg = 0;
int32_t ssid_rssi_min = 0;
int32_t ssid_rssi_max = 0;
int32_t ssid_rssi_avg = 0;


void loop() {
  display.display();
  display.clear();

  // WiFi.scanNetworks will return the number of networks found
  int n = WiFi.scanNetworks(false, true, true, 150); // bool async = false, bool show_hidden = false, bool passive = false, uint32_t max_ms_per_chan = 300

  if (set) {
    display.drawRect(126, 0, 2, 10);
  }
  set = !set;

  digitalWrite(LED_PIN, HIGH);
  if (n == 0) {
    //display.display();
    display.drawString(0, 0, "0 networks found");
    display.drawRect(120, 50, 2, 10);
  } else {
    display.drawString(0, 0, (String)n + " networks found");

    int yoff = 0;

    int count;
    int32_t rssi_min;
    int32_t rssi_max;
    int32_t rssi_total;

    //++++++++++++
    count = 0;
    rssi_min = INT_MAX;
    rssi_max = INT_MIN;
    rssi_total = 0;

    for (int i = 0; i < n; i++) {
      if (FOX_BSSID.equalsIgnoreCase(WiFi.BSSIDstr(i))) {
        count++;
        int32_t rssi = WiFi.RSSI(1);
        rssi_total += rssi;
        rssi_min = min(rssi_min, rssi);
        rssi_max = max(rssi_max, rssi);
      }
    }
    yoff++;
    display.drawString(0, yoff * 10, FOX_BSSID + "  #:" + count);

    if (count > 0) {
      digitalWrite(LED_PIN, LOW);
      bssid_rssi_max = rssi_max;
      bssid_rssi_avg = rssi_total / count;
      bssid_rssi_min = rssi_min;
    }
    yoff++;
    draw_measurements(yoff, bssid_rssi_max, bssid_rssi_avg, bssid_rssi_min);

    //++++++++++++
    count = 0;
    rssi_min = INT_MAX;
    rssi_max = INT_MIN;
    rssi_total = 0;

    for (int i = 0; i < n; i++) {
      if (FOX_SSID.equalsIgnoreCase(WiFi.SSID(i))) {
        count++;
        int32_t rssi = WiFi.RSSI(1);
        rssi_total += rssi;
        rssi_min = min(rssi_min, rssi);
        rssi_max = max(rssi_max, rssi);
      }
    }
    yoff++;
    display.drawString(0, yoff * 10, FOX_SSID + "  #:" + count);

    yoff++;
    if (count > 0) {
      digitalWrite(LED_PIN, LOW);
      ssid_rssi_max = rssi_max;
      ssid_rssi_avg = rssi_total / count;
      ssid_rssi_min = rssi_min;
    }
    draw_measurements(yoff, ssid_rssi_max, ssid_rssi_avg, ssid_rssi_min);

    yoff++;
    display.drawString(0, yoff * 10, "(   2.4Ghz AP Fox Hunter  )");
  }
}
