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

  WiFi.setHostname("ESP32");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    debug("Connecting to WiFi..");
  }
  Serial.println(WiFi.localIP());

  initWebSocket();
  CPU();

  debug("Config finish");
}

void CPU() {
  xTaskCreatePinnedToCore(
    Task1code,  
    "Task1",    
    10000,       
    NULL,        
    1,           
    &Task1,      
    0);          

  delay(500);

  xTaskCreatePinnedToCore(
    Task2code,   
    "Task2",     
    10000,       
    NULL,        
    1,           
    &Task2,      
    1);          

  delay(500);
}
