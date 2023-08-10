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

void setup() {
  config();
}

void loop() {} // only for arduino IDE
