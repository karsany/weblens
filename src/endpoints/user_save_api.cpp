#include <Arduino.h>
#include "endpoints/endpoints.h"
#include <Preferences.h>

void pictureSendSaveApi(AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total)
{

    const size_t        JSON_DOC_SIZE   = 512U;
    DynamicJsonDocument jsonDoc(JSON_DOC_SIZE);
    deserializeJson(jsonDoc, (const char*)data);

    JsonObject doc = jsonDoc.as<JsonObject>();

    Preferences preferences;
    preferences.begin("pictureSend", false);

    preferences.putString("pictureUrl", doc["pictureUrl"].as<String>());
    preferences.putString("extraJson", doc["extraJson"].as<String>());
    preferences.putInt("interval", doc["interval"].as<int>());

    preferences.end();


    request->send(200, "application/json", "{ \"status\": \"OK\" }");

    Serial.println("Settings saved, restarting ESP....");

    ESP.restart();

}

void pictureSendGetApi(AsyncWebServerRequest *request)
{
    DynamicJsonDocument doc(1024);

    Preferences preferences;
    preferences.begin("pictureSend", false);

    doc["pictureUrl"] = preferences.getString("pictureUrl", "###");
    doc["extraJson"] = preferences.getString("extraJson", "{}");
    doc["interval"] = preferences.getInt("interval", 10);

    preferences.end();

    String response;
    serializeJson(doc, response);

    request->send(200, "application/json", response);
}