void init_hvac() {
  pinMode(HVAC_HOT,  OUTPUT);
  pinMode(HVAC_COLD, OUTPUT);
  pinMode(HVAC_FAN,  OUTPUT);
  digitalWrite(HVAC_HOT,  HIGH);
  digitalWrite(HVAC_COLD, HIGH);
  digitalWrite(HVAC_FAN,  HIGH);
}

enum hvacMode { HEAT, COOL, OFF };
hvacMode hvac_mode = OFF;

unsigned long last_heat = 0;
unsigned long last_cool = 0;

void set_hvac(uint8_t cold, uint8_t hot, uint8_t fan, enum hvacMode m, String s);
void set_hvac(uint8_t cold, uint8_t hot, uint8_t fan, enum hvacMode m, String s) {
  digitalWrite(HVAC_COLD, cold);
  digitalWrite(HVAC_HOT, hot);
  digitalWrite(HVAC_FAN, fan);
  hvac_mode = m;
  hvac_string = s;
  redraw = true;
}
void start_heat() { set_hvac(HIGH, LOW,  LOW, HEAT, "Heat"); }
void start_cool() { set_hvac(LOW,  HIGH, LOW, COOL, "Cool"); }
void start_off()  { set_hvac(HIGH, HIGH, HIGH,  OFF, "Off");  }

void update_hvac() {
  if (hvac_mode == HEAT) {
    if (temp > config.target_temp) start_off();
    last_heat = millis();
  }
  else if (hvac_mode == COOL) {
    if (temp < config.target_temp) start_off();
    last_cool = millis();
  }
  else if (hvac_mode == OFF) {
    if (temp > config.target_temp + config.allowed_deviation && (last_heat == 0 || abs(millis() - last_heat) > config.minimum_switch_seconds * 1000)) start_cool();
    if (temp < config.target_temp - config.allowed_deviation && (last_cool == 0 || abs(millis() - last_cool) > config.minimum_switch_seconds * 1000)) start_heat();
  }
}
