float temps[3];
int temps_idx = -1;
int num_temps = (sizeof(temps)/sizeof(float));

unsigned long last_temp_time = 0;
bool need_temp_recalc = false;

void init_temperature() {
  temp_sensor.begin();
  float dirty = temp_sensor.computeHeatIndex(true);
  for (int i = 0; i < num_temps; i++) temps[i] = isnan(dirty) ? config.target_temp : dirty;
}

void update_temperature() {
  unsigned long now = millis();
  // Don't sample more often than once every 10 seconds
  if (abs(now - last_temp_time) > 10000) {
    float dirty;
    dirty = temp_sensor.readTemperature(true);
    if (!isnan(dirty)) temp_raw = dirty;
    dirty = temp_sensor.readHumidity();
    if (!isnan(dirty)) humidity = dirty;
    temps_idx = (temps_idx + 1) % num_temps;
    temps[temps_idx] = temp_sensor.computeHeatIndex(temp_raw, humidity, true);
    last_temp_time = now;
    need_temp_recalc = true;
  }
  if (need_temp_recalc) {
    temp = config.therm_offset;
    for (int i = 0; i < num_temps; i++) temp += (temps[i] / num_temps);
    redraw = true;
    need_temp_recalc = false;
  }
}
