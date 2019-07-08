void init_display() {
  display.init();
  display.clear();
  display.setColor(WHITE);
}

void update_display() {
  if (!redraw) return;
  redraw = false;
  display.clear();
  
  display.setFont(ArialMT_Plain_24);
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.drawString(15, 5, String(temp, 1) + "°");
  
  display.setFont(ArialMT_Plain_16);
  display.setTextAlignment(TEXT_ALIGN_RIGHT);
  display.drawString(120, 12, String(config.target_temp, 1) + "°");
  
  display.setFont(ArialMT_Plain_10);
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.drawString(15, 35, String(humidity, 0) + "%");

  display.drawString(85, 35, hvac_string);

  if (should_show_ip) {
    display.setTextAlignment(TEXT_ALIGN_RIGHT);
    display.drawString(120, 50, WiFi.status() == WL_CONNECTED ? WiFi.localIP().toString() : "X");
  }
  
  display.display();
}
