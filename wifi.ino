#define HOSTNAME "Thermostat"
#define AP_PASS  "hunter2"

unsigned long time_showed_ip = 0;

void update_show_ip() {
  if (!should_show_ip) return;
  if (!time_showed_ip) {
    time_showed_ip = millis();
    redraw = true;
  } else if (time_showed_ip + 2000 < millis()) {
    should_show_ip = false;
    time_showed_ip = 0;
    redraw = true;
  }
}

bool trying_AP = false;
unsigned long start_connect_time = 0;
unsigned long start_AP_time = 0;

void init_wifi() {
  start_wifi();
}

void start_wifi() {
  WiFi.softAPdisconnect();
  start_connect_time = millis();
  WiFi.begin(config.wifi_ssid, config.wifi_pass);
}

void start_ap() {
  start_AP_time = millis();
  trying_AP = true;
  WiFi.disconnect();
  WiFi.softAP(HOSTNAME, AP_PASS);
}

void update_wifi() {
  update_show_ip();
  // If we're connected to WiFi, nothing needs to be done
  if (WiFi.status() == WL_CONNECTED) return;
  // If we've been trying to connect to a network for over 8 seconds, bail and spin up an AP
  if (!trying_AP && abs(millis() - start_connect_time) > 8000) start_ap();
  // If we've been running an AP for 5 minutes, try connecting to WiFi again
  if (trying_AP && abs(millis() - start_AP_time) > 300000) init_wifi();
}
