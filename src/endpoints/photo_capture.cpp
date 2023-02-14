#include "endpoints/endpoints.h"
#include "photo/photo.h"

void photoCaptureApi(AsyncWebServerRequest *request)
{
    askForPhoto();
    request->send(200, "application/json", "{ \"status\": \"OK\" }");
}