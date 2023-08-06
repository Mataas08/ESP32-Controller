#include <Arduino.h>
#include <soc/soc.h>
#include <soc/rtc_cntl_reg.h>
#include <soc/rtc_wdt.h>
#include "SPIFFS.h"
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <AsyncTCP.h>
#include <AsyncElegantOTA.h>
#include "config.h"
#include "program.h"
#include "web.h"

void program();

void setup() {
  config();
}

void loop() { // only for arduino IDE
}

void program() {
  Serial.print("|" + String(LEFT_SHOULDER_BOTTOM) + "|" + String(RIGHT_SHOULDER_BOTTOM) + "|" + String(LEFT_ANALOG_STICK_X) + "|" + String(LEFT_ANALOG_STICK_Y) + "|" + String(RIGHT_ANALOG_STICK_X) + "|" + String(RIGHT_ANALOG_STICK_Y) + "|");
  Serial.print("|");
  Serial.print("|" + String(FACE_1) + "|" + String(FACE_2) + "|" + String(FACE_3) + "|" + String(FACE_4) + "|");
  Serial.print("|");
  Serial.print("|" + String(DPAD_UP) + "|" + String(DPAD_DOWN) + "|" + String(DPAD_LEFT) + "|" + String(DPAD_RIGHT) + "|");
  Serial.print("|");
  Serial.print("|" + String(LEFT_SHOULDER) + "|" + String(RIGHT_SHOULDER) + "|" + String(LEFT_ANALOG_BUTTON) + "|" + String(RIGHT_ANALOG_BUTTON) + "|");
  Serial.print("|");
  Serial.println("|" + String(START) + "|" + String(SELECT) + "|" + String(HOME) + "|");
}
