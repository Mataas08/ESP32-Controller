#include "program.h"
#include "config.h"

void Task1code( void * pvParameters ) {
  debug("Task1 is running on core: " + String(xPortGetCoreID()));

  web();
  asyncOTA();
  server.begin();

  for (;;) {
    ws.cleanupClients();
    delay(1);
  }
}

void Task2code( void * pvParameters ) {
  debug("Task2 is running on core: " + String(xPortGetCoreID()));

  for (;;) {
    program();
  }
}

void asyncOTA() {
  AsyncElegantOTA.begin(&server);
}

void debug(String text) {
  Serial.println(text);
}
