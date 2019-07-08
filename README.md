# Thermostat

This repository contains the firmware for the custom-built thermostat described in [this blog post](https://blog.benhaney.com/2019/03/26/building-a-thermostat).

## Schematics
![Schematics](schematic.png?raw=true)

## API

### GET /
```
{
  "temp": 70.03,      // The displayed temperature (rolling average of heat index adjusted by configured sensor offset)
  "temp_raw": 71.47,  // The latest raw temperature from the sensor
  "humidity": 50,     // The latest raw percent humidity from the sensor
  "heatindex": 71.53, // The heat index calculated from raw temperature and humidity
  "status": "Off"     // Current HVAC status (Off, Cool, Heat)
}
```

### GET /config
```
{
  "wifi_ssid": "myssid",         // WiFi SSID
  "wifi_pass": "[hidden]",       // WiFi Password (never shown)
  "target_temp": 70.0,           // Desired room temperature
  "allowed_deviation": 0.7,      // Allowed deviation from desired temperature before the HVAC is kicked on
  "minimum_switch_seconds": 600, // Minimum allowed time to switch between heat and cool or vice versa
  "therm_offset": -1.5           // Adjustment applied to temperature sensor
}
```

### POST /config
Sets any of the keys from the GET response to the provided value. Causes a reboot if WiFi credentials are changed.
