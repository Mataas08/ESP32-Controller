#include "config.h"

void config() {
  Serial.begin(115200);
  delay(100);
  debug("Welcome");
  debug("setup is running on core: " + String(xPortGetCoreID()));

  if (!SPIFFS.begin(true)) {
    debug("SPIFFS.begin: ERR");
    return;
  } else {
    debug("SPIFFS.begin: OK");
  }

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    debug("Connecting to WiFi..");
  }
  debug(String(WiFi.localIP()));

  initWebSocket();

  CPU();

  debug("Config finish");
}

void CPU() {
  xTaskCreatePinnedToCore(
    Task1code,   /* Task function. */
    "Task1",     /* name of task. */
    10000,       /* Stack size of task */
    NULL,        /* parameter of the task */
    1,           /* priority of the task */
    &Task1,      /* Task handle to keep track of created task */
    0);          /* pin task to core 0 */

  delay(500);

  xTaskCreatePinnedToCore(
    Task2code,   /* Task function. */
    "Task2",     /* name of task. */
    10000,       /* Stack size of task */
    NULL,        /* parameter of the task */
    1,           /* priority of the task */
    &Task2,      /* Task handle to keep track of created task */
    1);          /* pin task to core 1 */

  delay(500);
}
