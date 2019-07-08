#include <EEPROM.h>
#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>
#include <DHT.h>
#include <SSD1306Brzo.h>

#define DISPLAY_SDA D3
#define DISPLAY_SCL D4
#define TEMP_SENSOR D5
#define BUTTON_UP   D6
#define BUTTON_DOWN D8
#define HVAC_HOT    D7
#define HVAC_COLD   D9
#define HVAC_FAN    D10

float temp = 68.0;
float temp_raw = 68.0;
float humidity = 50;
bool redraw = true;
String hvac_string = "Off";
bool should_show_ip = false;

struct Config {
  char wifi_ssid[33] = "";
  char wifi_pass[33] = "";
  float target_temp = 68.0;
  float allowed_deviation = 0.7;
  uint32_t minimum_switch_seconds = 600;
  float therm_offset = 0.0;
} config;

ESP8266WebServer server(80);
SSD1306Brzo      display(0x3c, DISPLAY_SDA, DISPLAY_SCL);
DHT              temp_sensor(TEMP_SENSOR, DHT22);

void setup() {
  init_eeprom();
  init_hvac();
  init_buttons();
  init_temperature();
  init_display();
  init_wifi();
  init_webserver();

  delay(10);
}

void reset() { while (1) {} }

void loop() {
  update_hvac();
  update_webserver();
  update_temperature();
  update_wifi();
  update_display();
}
