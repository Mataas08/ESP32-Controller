#include "web.h"
#include "config.h"

void handleWebSocketMessage(void *arg, uint8_t *data, size_t len) {
  AwsFrameInfo *info = (AwsFrameInfo*)arg;
  if (info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT) {
    data[len] = 0;
    message = (char*)data;

    if (String(message.substring(0, 5)) == "LSB__") {
      LEFT_SHOULDER_BOTTOM = message.substring(5, 9).toFloat();
    }
    if (String(message.substring(0, 5)) == "RSV__") {
      RIGHT_SHOULDER_BOTTOM = message.substring(5, 9).toFloat();
    }
    if (String(message.substring(0, 5)) == "LAS_X") {
      LEFT_ANALOG_STICK_X = message.substring(5, 9).toFloat();
    }
    if (String(message.substring(0, 5)) == "LAS_Y") {
      LEFT_ANALOG_STICK_Y = message.substring(5, 9).toFloat();
    }
    if (String(message.substring(0, 5)) == "RAS_X") {
      RIGHT_ANALOG_STICK_X = message.substring(5, 9).toFloat();
    }
    if (String(message.substring(0, 5)) == "RAS_Y") {
      RIGHT_ANALOG_STICK_Y = message.substring(5, 9).toFloat();
    }

    if (String(message.substring(0, 5)) == "F1___") {
      FACE_1 = message.substring(5, 6).toFloat();
    }
    if (String(message.substring(0, 5)) == "F2___") {
      FACE_2 = message.substring(5, 6).toFloat();
    }
    if (String(message.substring(0, 5)) == "F3___") {
      FACE_3 = message.substring(5, 6).toFloat();
    }
    if (String(message.substring(0, 5)) == "F4___") {
      FACE_4 = message.substring(5, 6).toFloat();
    }

    if (String(message.substring(0, 5)) == "D1___") {
      DPAD_UP = message.substring(5, 6).toFloat();
    }
    if (String(message.substring(0, 5)) == "D2___") {
      DPAD_DOWN = message.substring(5, 6).toFloat();
    }
    if (String(message.substring(0, 5)) == "D3___") {
      DPAD_LEFT = message.substring(5, 6).toFloat();
    }
    if (String(message.substring(0, 5)) == "D4___") {
      DPAD_RIGHT = message.substring(5, 6).toFloat();
    }

    if (String(message.substring(0, 5)) == "LS___") {
      LEFT_SHOULDER = message.substring(5, 6).toFloat();
    }
    if (String(message.substring(0, 5)) == "RS___") {
      RIGHT_SHOULDER = message.substring(5, 6).toFloat();
    }
    if (String(message.substring(0, 5)) == "LAB__") {
      LEFT_ANALOG_BUTTON = message.substring(5, 6).toFloat();
    }
    if (String(message.substring(0, 5)) == "RAB__") {
      RIGHT_ANALOG_BUTTON = message.substring(5, 6).toFloat();
    }

    if (String(message.substring(0, 5)) == "ST___") {
      START = message.substring(5, 6).toFloat();
    }
    if (String(message.substring(0, 5)) == "SL___") {
      SELECT = message.substring(5, 6).toFloat();
    }
    if (String(message.substring(0, 5)) == "H____") {
      HOME = message.substring(5, 6).toFloat();
    }

    //Serial.println("|"+String(LEFT_SHOULDER_BOTTOM)+"|"+String(RIGHT_SHOULDER_BOTTOM)+"|"+String(LEFT_ANALOG_STICK_X)+"|"+String(LEFT_ANALOG_STICK_Y)+"|"+String(RIGHT_ANALOG_STICK_X)+"|"+String(RIGHT_ANALOG_STICK_Y)+"|");
    //Serial.println("|" + String(FACE_1) + "|" + String(FACE_2) + "|" + String(FACE_3) + "|" + String(FACE_4) + "|");
    //Serial.println("|" + String(DPAD_UP) + "|" + String(DPAD_DOWN) + "|" + String(DPAD_LEFT) + "|" + String(DPAD_RIGHT) + "|");
    //Serial.println("|" + String(LEFT_SHOULDER) + "|" + String(RIGHT_SHOULDER) + "|" + String(LEFT_ANALOG_BUTTON) + "|" + String(RIGHT_ANALOG_BUTTON) + "|");
    //Serial.println("|" + String(START) + "|" + String(SELECT) + "|" + String(HOME) + "|");
  }
}

void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len) {
  switch (type) {
    case WS_EVT_CONNECT:
      Serial.printf("WebSocket client #%u connected from %s\n", client->id(), client->remoteIP().toString().c_str());
      break;
    case WS_EVT_DISCONNECT:
      Serial.printf("WebSocket client #%u disconnected\n", client->id());
      break;
    case WS_EVT_DATA:
      handleWebSocketMessage(arg, data, len);
      break;
    case WS_EVT_PONG:
    case WS_EVT_ERROR:
      break;
  }
}

void initWebSocket() {
  ws.onEvent(onEvent);
  server.addHandler(&ws);
}

String processor(const String& var) {
  Serial.println(var);
  return String();
}

void web() {
  server.on("/", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/index.html", String(), false, processor);
  });

  server.on("/js/Controller.js", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/js/Controller.js", "text/css");
  });

  server.on("/js/Controller.layouts.js", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/js/Controller.layouts.js", "text/css");
  });

  server.on("/js/dat.gui.min.js", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/js/dat.gui.min.js", "text/css");
  });

  server.on("/js/main.js", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/js/main.js", "text/css");
  });

  server.on("/styles/style.css", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/styles/style.css", "text/css");
  });
}
