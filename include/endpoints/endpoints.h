#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>


void settingsApi(AsyncWebServerRequest *request);

void settingsResetApi(AsyncWebServerRequest *request);

void photoCaptureApi(AsyncWebServerRequest *request);

void photoDownloadApi(AsyncWebServerRequest *request);

void pictureSendSaveApi(AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total);

void pictureSendGetApi(AsyncWebServerRequest *request);