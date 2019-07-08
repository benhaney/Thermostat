String data;

void init_webserver() {
  server.begin();
  server.on("/", HTTP_GET, []() {
    data = "{";
    data += "\"temp\":" + String(temp) + ",";
    data += "\"temp_raw\":" + String(temp_raw) + ",";
    data += "\"humidity\":" + String(humidity) + ",";
    data += "\"heatindex\":" + String(temps_idx >= 0 ? temps[temps_idx] : 0) + ",";
    data += "\"status\":\"" + hvac_string + "\"";
    data += "}";
    server.send(200, "application/json", data);
  });

  server.on("/config", HTTP_GET, []() {
    data = "{";
    data += String("\"wifi_ssid\":\"") + config.wifi_ssid + "\",";
    // data += String("\"wifi_pass\":\"") + config.wifi_pass + "\",";
    data += String("\"wifi_pass\":\"[hidden]\",");
    data += String("\"target_temp\":") + String(config.target_temp) + ",";
    data += String("\"allowed_deviation\":") + String(config.allowed_deviation) + ",";
    data += String("\"minimum_switch_seconds\":") + String(config.minimum_switch_seconds) + ",";
    data += String("\"therm_offset\":") + String(config.therm_offset);
    data += "}";
    server.send(200, "application/json", data);
  });

  server.on("/config", HTTP_POST, []() {
    /*
    if (!server.hasArg("auth") || server.arg("auth") != "some_secret_key") {
      server.send(401, "application/json", "{\"err\":\"incorrect auth key\"}");
      return;
    }
    */

    bool needs_reboot = false;

    if (server.hasArg("wifi_ssid")) {
      server.arg("wifi_ssid").toCharArray(config.wifi_ssid, 33);
      needs_reboot = true;
    }
    if (server.hasArg("wifi_pass")) {
      server.arg("wifi_pass").toCharArray(config.wifi_pass, 33);
      needs_reboot = true;
    }
    if (server.hasArg("target_temp")) {
      config.target_temp = server.arg("target_temp").toFloat();
    }
    if (server.hasArg("allowed_deviation")) {
      config.allowed_deviation = server.arg("allowed_deviation").toFloat();
    }
    if (server.hasArg("minimum_switch_seconds")) {
      config.minimum_switch_seconds = server.arg("minimum_switch_seconds").toInt();
    }
    if (server.hasArg("therm_offset")) {
      config.therm_offset = server.arg("therm_offset").toFloat();
      need_temp_recalc = true;
    }

    redraw = true;
    update_eeprom();

    if (needs_reboot) {
      server.send(200, "application/json", "{\"rebooting\":true}");
      delay(100);
      reset();
    } else {
      server.send(200, "application/json", "{\"rebooting\":false}");
    }
  });
}

void update_webserver() {
  server.handleClient();
  
}
