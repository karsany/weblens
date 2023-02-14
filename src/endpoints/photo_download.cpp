#include "endpoints/endpoints.h"
#include "photo/photo.h"

void photoDownloadApi(AsyncWebServerRequest *request)
{
    request->send_P(200, "image/jpeg", getPP(), getPicSize());
}