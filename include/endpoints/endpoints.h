#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>


void settingsApi(AsyncWebServerRequest *request);

void settingsResetApi(AsyncWebServerRequest *request);

void photoCaptureApi(AsyncWebServerRequest *request);

void photoDownloadApi(AsyncWebServerRequest *request);

void userSaveApi(AsyncWebServerRequest *request);