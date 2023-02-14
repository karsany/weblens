#include "endpoints/endpoints.h"
#include <nvs_flash.h>

void settingsResetApi(AsyncWebServerRequest *request)
{
    nvs_flash_erase();
    nvs_flash_init();

    request->send(200, "application/json", "{ \"status\": \"OK\" }");

    Serial.println("NVS erased, restarting ESP....");

    ESP.restart();
}