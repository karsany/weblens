#include "endpoints/endpoints.h"

void userSaveApi(AsyncWebServerRequest *request)
{

    request->send(200, "application/json", "{ \"status\": \"OK\" }");
}