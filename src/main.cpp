#include "Arduino.h"
#include <ESP8266WiFi.h>
#include <ArduinoOTA.h>
#include "config.h"
#include "http_server.h"


void wifi_setup()
{
    WiFi.hostname(CONFIG_WIFI_HOSTNAME);
    WiFi.mode(WIFI_STA);
    WiFi.begin(CONFIG_WIFI_SSID, CONFIG_WIFI_PASSWORD);
    while (WiFi.status() != WL_CONNECTED) {
        delay(10);
    }
}

void ota_setup()
{
    ArduinoOTA.setPort(CONFIG_OTA_PORT);
    ArduinoOTA.setHostname(CONFIG_OTA_HOSTNAME);
    #ifdef CONFIG_OTA_PASSWORD
    ArduinoOTA.setPassword(CONFIG_OTA_PASSWORD);
    #endif

    ArduinoOTA.onStart([]() {
        String type;
        if (ArduinoOTA.getCommand() == U_FLASH) {
          type = "sketch";
        } else { // U_FS
          type = "filesystem";
        }

        // NOTE: if updating FS this would be the place to unmount FS using FS.end()
        Serial.println("\nOTA Start " + type);   
    });
    ArduinoOTA.onEnd([]() {
        Serial.println("\nOTA End");
    });
    ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
        Serial.printf("OTA Progress: %u%%\r\n", (progress / (total / 100)));
    });
    ArduinoOTA.onError([](ota_error_t error) {
        Serial.printf("OTA Error[%u]: ", error);
        if (error == OTA_AUTH_ERROR) {
          Serial.println("Auth Failed");
        } else if (error == OTA_BEGIN_ERROR) {
          Serial.println("Begin Failed");
        } else if (error == OTA_CONNECT_ERROR) {
          Serial.println("Connect Failed");
        } else if (error == OTA_RECEIVE_ERROR) {
          Serial.println("Receive Failed");
        } else if (error == OTA_END_ERROR) {
          Serial.println("End Failed");
        }
    });
    ArduinoOTA.begin();
    Serial.println("ota ready");
}
void ota_loop() {
    ArduinoOTA.handle();
}

void eeprom_setup()
{
//     EEPROM.begin(EEPROM_FULL_SIZE);

//     uint8_t cookie = EEPROM.read(EEPROM_ADDR_MAGIC);
//     if (cookie != EEPROM_MAGIC_COOKIE) {
//         // format eeprom with defaults
        
//     }
}

void setup()
{
    Serial.begin(74880);
    Serial.println("hello schoolbell");

    wifi_setup();
    ota_setup();

    eeprom_setup();
    httpd_setup();
    Serial.println("setup complete");

    tone(SPEAKER_PIN, 110, 1800);
}


void loop() 
{
    httpd_loop();
    ota_loop();
}