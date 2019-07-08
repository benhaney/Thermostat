void init_buttons() {
  pinMode(BUTTON_UP,   INPUT);
  pinMode(BUTTON_DOWN, INPUT);
  attachInterrupt(digitalPinToInterrupt(BUTTON_UP),   button_up_pressed,   CHANGE);
  attachInterrupt(digitalPinToInterrupt(BUTTON_DOWN), button_down_pressed, CHANGE);
}

bool buttons_state[2] = {false, false};
unsigned long buttons_last[2] = {0, 0};

void button_up_pressed() { button_pressed(0, 1.0, BUTTON_UP); }
void button_down_pressed() { button_pressed(1, -1.0, BUTTON_DOWN); }

void button_pressed(uint8_t b, float dir, uint8_t pin) {
  bool button_pressed = digitalRead(pin);
  if (button_pressed == buttons_state[b]) return;
  if (buttons_state[b]) {
    unsigned long time_pressed = abs(millis() - buttons_last[b]);
    if (time_pressed > 20) {
      config.target_temp += dir * ((time_pressed > 250) ? 1.0 : 0.2);
      should_show_ip = true;
      update_eeprom();
      redraw = true;
    }
    buttons_state[b] = false;
  } else {
    buttons_last[b] = millis();
    buttons_state[b] = true;
  }
}
