#include "endpoints/endpoints.h"
#include "WiFi.h"
#include "version.cpp"

void settingsApi(AsyncWebServerRequest *request)
{
    DynamicJsonDocument doc(1024);

    doc["ip"] = WiFi.localIP();
    doc["ssid"] = WiFi.SSID();
    doc["mac"] = WiFi.macAddress();
    doc["version"] = APP_VERSION;

    String response;
    serializeJson(doc, response);

    request->send(200, "application/json", response);
}