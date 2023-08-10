#ifndef CONFIG_H_
#define CONFIG_H_

void config();
void CPU();

TaskHandle_t Task1;
TaskHandle_t Task2;

#define _ASYNC_WEBSERVER_LOGLEVEL_ 2

const char* ssid = "#$%!**";
const char* password = "@#$%*!";

File file;

AsyncWebServer server(80);
AsyncWebSocket ws("/ws");

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

#endif
