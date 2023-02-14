#include <Arduino.h>
#include <Preferences.h>
#include <WiFi.h>
#include <wifi_settings.h>
#include <ESPmDNS.h>

#define LED_BUILTIN 4

long ledState = LOW;

void toggleLedState()
{
    if (ledState == LOW)
    {
        ledState = HIGH;
    }
    else
    {
        ledState = LOW;
    }
    digitalWrite(LED_BUILTIN, ledState);
}

void successLed()
{
    toggleLedState();
    delay(200);
    toggleLedState();
    delay(200);
    toggleLedState();
    delay(200);
    toggleLedState();
    delay(200);
    toggleLedState();
    delay(200);
    toggleLedState();
    delay(200);
    toggleLedState();
    delay(200);
    toggleLedState();
    delay(200);
    digitalWrite(LED_BUILTIN, LOW);
}

bool tryConnect(int seconds)
{

    int sec = 0;

    Preferences preferences;
    preferences.begin("cred", false);
    String ssid = preferences.getString("ssid", "none");
    String password = preferences.getString("password", "none");
    preferences.end();

    WiFi.begin(ssid.c_str(), password.c_str());

    /* Wait for WiFi to connect to AP */

    Serial.println("Waiting for WiFi: ");
    Serial.println(ssid);

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
        sec++;
        if (sec > 2 * seconds)
        {
            return false;
        }
    }
    return true;
}

void trySmartconfig(int seconds)
{

    int sec = 0;

    /* start SmartConfig */
    WiFi.beginSmartConfig();

    /* Wait for SmartConfig packet from mobile */
    Serial.println("Waiting for SmartConfig.");
    while (!WiFi.smartConfigDone())
    {
        delay(500);
        Serial.print(".");
        toggleLedState();
        sec++;
        if (sec > seconds * 2)
        {
            digitalWrite(LED_BUILTIN, LOW);
            WiFi.stopSmartConfig();
            Serial.println("SmartConfig not finished. Restarting....");
            ESP.restart();
        }
    }

    Preferences preferences;
    preferences.begin("cred", false);
    preferences.putString("ssid", WiFi.SSID());
    preferences.putString("password", WiFi.psk());
    preferences.putBool("wifi-set", true);
    preferences.end();

    Serial.println("");
    Serial.println("SmartConfig done, credentials saved.");

    WiFi.stopSmartConfig();
    successLed();

    Serial.println("SmartConfig done, credentials restart cam");
    ESP.restart();
}

void initWifi()
{

    Preferences preferences;
    preferences.begin("cred", false);
    bool wifiSet = preferences.getBool("wifi-set", false);
    preferences.end();

    // init before
    WiFi.mode(WIFI_AP_STA);
    pinMode(LED_BUILTIN, OUTPUT);

    bool successful = false;

    // init wifi data -- after successful initialization

    if (wifiSet)
    {
        successful = tryConnect(30);
    }

    if (!successful || !wifiSet)
    {
        trySmartconfig(60);
    }

    WiFi.setHostname("weblens-admin");

    Serial.println("WiFi hostname: weblens-admin");

    Serial.println("WiFi Connected.");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());

    if (!MDNS.begin("weblens"))
    {
        Serial.println("Error starting mDNS");
        return;
    }

    MDNS.addService("http", "tcp", 80);
    MDNS.addServiceTxt("http", "tcp", "name", "WebLens Administration Console");

    Serial.println("mDNS hostname: weblens");
}