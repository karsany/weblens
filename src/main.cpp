#include <Arduino.h>
#include "wifi_settings.h"
#include "cam_webserver.h"
#include "photo/photo.h"

void setup()
{
  Serial.begin(115200);
  Serial.setDebugOutput(true);
  Serial.flush();
  initWifi();
  initSPIFFS();
  initCamera();
  initServer();
}

void loop()
{
  handlePhoto();
  delay(1);
}