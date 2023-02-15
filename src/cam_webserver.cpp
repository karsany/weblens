#include "webserver.h"
#include "indexhtml.cpp"
#include "endpoints/endpoints.h"

AsyncWebServer server(80);

void initServer()
{

  DefaultHeaders::Instance().addHeader(F("Access-Control-Allow-Origin"), F("*"));
  DefaultHeaders::Instance().addHeader(F("Access-Control-Allow-Headers"), F("content-type"));

  server.on("/api/photo/capture", HTTP_GET, &photoCaptureApi);
  server.on("/api/photo/download", HTTP_GET, &photoDownloadApi);
  server.on("/api/settings/reset", HTTP_GET, &settingsResetApi);
  server.on("/api/settings/picture_send", HTTP_GET, &pictureSendGetApi);
  server.on("/api/settings/picture_send/save", HTTP_POST, [](AsyncWebServerRequest* req){}, NULL, &pictureSendSaveApi);
  server.on("/api/settings", HTTP_GET, &settingsApi);

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
            { request->send_P(200, "text/html", index_html); });
  server.onNotFound([](AsyncWebServerRequest *request)
                    { request->send_P(200, "text/html", index_html); });

  server.begin();
}