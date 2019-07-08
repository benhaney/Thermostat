void init_eeprom() {
  EEPROM.begin(96);
  if (EEPROM.read(0) != 0b10101010) return;
  EEPROM.get(1, config);
}

void update_eeprom() {
  EEPROM.write(0, 0b10101010);
  EEPROM.put(1, config);
  EEPROM.commit();
}
