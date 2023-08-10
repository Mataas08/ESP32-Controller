#include "program.h"
#include "config.h"

void Task1code( void * pvParameters ) {
  debug("Task1 is running on core: " + String(xPortGetCoreID()));

  web();
  asyncOTA();
  server.begin();

  for (;;) {
    ws.cleanupClients();

    Serial.print("|" + String(LEFT_SHOULDER_BOTTOM) + "|" + String(RIGHT_SHOULDER_BOTTOM) + "|" + String(LEFT_ANALOG_STICK_X) + "|" + String(LEFT_ANALOG_STICK_Y) + "|" + String(RIGHT_ANALOG_STICK_X) + "|" + String(RIGHT_ANALOG_STICK_Y) + "|");
    Serial.print("|");
    Serial.print("|" + String(FACE_1) + "|" + String(FACE_2) + "|" + String(FACE_3) + "|" + String(FACE_4) + "|");
    Serial.print("|");
    Serial.print("|" + String(DPAD_UP) + "|" + String(DPAD_DOWN) + "|" + String(DPAD_LEFT) + "|" + String(DPAD_RIGHT) + "|");
    Serial.print("|");
    Serial.print("|" + String(LEFT_SHOULDER) + "|" + String(RIGHT_SHOULDER) + "|" + String(LEFT_ANALOG_BUTTON) + "|" + String(RIGHT_ANALOG_BUTTON) + "|");
    Serial.print("|");
    Serial.println("|" + String(START) + "|" + String(SELECT) + "|" + String(HOME) + "|");

    delay(1);
  }
}

void Task2code( void * pvParameters ) {
  debug("Task2 is running on core: " + String(xPortGetCoreID()));

  for (;;) {
    if (String(FACE_1) == "1") {
      VIBRATION = 100;
      notifyClients();
      delay(1000);
      VIBRATION = 0;
      notifyClients();
      delay(500);
      VIBRATION = 50;
      notifyClients();
      delay(1000);
      VIBRATION = 0;
      notifyClients();
      delay(500);
      VIBRATION = 25;
      notifyClients();
      delay(1000);
      VIBRATION = 0;
      notifyClients();
      delay(500);
    }
  }
}

void asyncOTA() {
  AsyncElegantOTA.begin(&server);
}

void debug(String text) {
  Serial.println(text);
}
