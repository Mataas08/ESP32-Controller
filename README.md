# ESP32-Controller

A program that allows you to remotely control the ESP32 module via wifi using a game controller connected via bluetooth or usb to your computer.

- This code is for ESP32 and SPIFFS memory
- Program is for arduino IDE

## Features
 - Web control
 - based on Controller.js
 - OTA over web
 - easy use

### Setting
wifi password in config.h
```cpp
const char* ssid = "#$%!**";
const char* password = "@#$%*!";
```

### Usage
Program use 2 core. for this example pleas do not write in loop but 
```cpp
void Task1code( void * pvParameters ) {
...
 for (;;) {
  ...
 }
}
```
and
```cpp
void Task2code( void * pvParameters ) {
...
 for (;;) {
  ...
 }
}
```

controller variable 
```cpp
byte VIBRATION = 0;

float LEFT_ANALOG_STICK_X = 0.00;
float LEFT_ANALOG_STICK_Y = 0.00;
float RIGHT_ANALOG_STICK_X = 0.00;
float RIGHT_ANALOG_STICK_Y = 0.00;
bool FACE_1 = 0;
bool FACE_2 = 0;
bool FACE_3 = 0;
bool FACE_4 = 0;
bool LEFT_SHOULDER = 0;
bool RIGHT_SHOULDER = 0;
float LEFT_SHOULDER_BOTTOM = 0.00;
float RIGHT_SHOULDER_BOTTOM = 0.00;
bool SELECT = 0;
bool START = 0;
bool LEFT_ANALOG_BUTTON = 0;
bool RIGHT_ANALOG_BUTTON = 0;
bool DPAD_UP = 0;
bool DPAD_DOWN = 0;
bool DPAD_LEFT = 0;
bool DPAD_RIGHT = 0;
bool HOME = 0;
```
if you want turn on and off vibration you can change a "VIBRATION" wariabla betwen 0 to 100 (it is power)

### OTA
ota is available on http://hostname/update
