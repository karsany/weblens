#include "photo/photo.h"
#include <SPIFFS.h>
#include "esp_camera.h"
#include "soc/soc.h"          // Disable brownour problems
#include "soc/rtc_cntl_reg.h" // Disable brownour problems

#define LED_BUILTIN 4

bool takeNewPhoto = false;
uint8_t *picPointer = NULL;
long picSize = 0;

void initSPIFFS()
{

    if (!SPIFFS.begin(true))
    {
        Serial.println("An Error has occurred while mounting SPIFFS");
        ESP.restart();
    }
    else
    {
        delay(500);
        Serial.println("SPIFFS mounted successfully");
    }
}

void initCamera()
{

    WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0);

    // OV2640 camera module
    camera_config_t config;
    config.ledc_channel = LEDC_CHANNEL_0;
    config.ledc_timer = LEDC_TIMER_0;
    config.pin_d0 = Y2_GPIO_NUM;
    config.pin_d1 = Y3_GPIO_NUM;
    config.pin_d2 = Y4_GPIO_NUM;
    config.pin_d3 = Y5_GPIO_NUM;
    config.pin_d4 = Y6_GPIO_NUM;
    config.pin_d5 = Y7_GPIO_NUM;
    config.pin_d6 = Y8_GPIO_NUM;
    config.pin_d7 = Y9_GPIO_NUM;
    config.pin_xclk = XCLK_GPIO_NUM;
    config.pin_pclk = PCLK_GPIO_NUM;
    config.pin_vsync = VSYNC_GPIO_NUM;
    config.pin_href = HREF_GPIO_NUM;
    config.pin_sscb_sda = SIOD_GPIO_NUM;
    config.pin_sscb_scl = SIOC_GPIO_NUM;
    config.pin_pwdn = PWDN_GPIO_NUM;
    config.pin_reset = RESET_GPIO_NUM;
    config.xclk_freq_hz = 20000000;
    config.pixel_format = PIXFORMAT_JPEG;

    if (psramFound())
    {
        config.frame_size = FRAMESIZE_UXGA;
        config.jpeg_quality = 10;
        config.fb_count = 2;
    }
    else
    {
        config.frame_size = FRAMESIZE_SVGA;
        config.jpeg_quality = 12;
        config.fb_count = 1;
    }
    // Camera init
    esp_err_t err = esp_camera_init(&config);
    if (err != ESP_OK)
    {
        Serial.printf("Camera init failed with error 0x%x", err);
        ESP.restart();
    }
}

void flashOn()
{
    digitalWrite(LED_BUILTIN, HIGH);
}

void flashOff()
{
    digitalWrite(LED_BUILTIN, LOW);
}

void capturePhotoSaveSpiffs(void)
{

    Serial.print("Free HEAP/PSRAM before capture: ");
    Serial.println(ESP.getFreeHeap());
    Serial.println(ESP.getFreePsram());

    camera_fb_t *fb = NULL; // pointer
    bool ok = 0;            // Boolean indicating if the picture has been taken correctly

    do
    {
        // Take a photo with the camera
        Serial.println("Taking a photo...");

        flashOn();
        delay(1000);

        fb = esp_camera_fb_get();
        esp_camera_fb_return(fb);
        fb = esp_camera_fb_get();
        esp_camera_fb_return(fb);
        fb = esp_camera_fb_get();
        esp_camera_fb_return(fb);
        if (!fb)
        {
            Serial.println("Camera capture failed");
            return;
        }

        if (picPointer != NULL)
        {
            free(picPointer);
        }
        picPointer = (uint8_t *)malloc(fb->len);

        if (picPointer == NULL)
        {
            Serial.println("Out of memory");
            return;
        }
        memcpy(picPointer, fb->buf, fb->len);
        picSize = fb->len;

        Serial.println("Photo saved into memory");
        Serial.print(picSize);
        Serial.println(" bytes");

        esp_camera_fb_return(fb);
        flashOff();

        // check if file has been correctly saved in SPIFFS
        ok = true; // checkPhoto(SPIFFS);
    } while (!ok);

    Serial.print("Free HEAP/PSRAM after capture: ");
    Serial.println(ESP.getFreeHeap());
    Serial.println(ESP.getFreePsram());
}

void handlePhoto()
{
    if (takeNewPhoto)
    {
        capturePhotoSaveSpiffs();
        takeNewPhoto = false;
    }
}

void askForPhoto()
{
    takeNewPhoto = true;
}

uint8_t *getPP()
{
    return picPointer;
}

long getPicSize()
{
    return picSize;
}