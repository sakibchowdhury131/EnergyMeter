# Energy Meter 
- Overview
    -
- AVR chip is used for all measurements
- UART communication between AVR and ESP8266: 
    - The measurements are sent to ESP8266 via UART communication.
- ESP8266 sends data to the MQTT server via internet and WiFi. 
    - for testing purpose, you can use opensource MQTT servers such as mosquitto or adafruit.io

- File System
    -
    - ignore the test folder, it is here just for some debugging purpose
    - the firmware folder contains 2 subfolders: powerMeasure and MQTT_client
    - upload the powerMeasure firmware in the AVR chip
    - upload the MQTT_client firmware to ESP8266

- License
    -
    - Author: Sakib Chowdhury
    - opensource software under MIT License