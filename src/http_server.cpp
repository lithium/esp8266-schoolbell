#include "http_server.h"

ESP8266WebServer httpd;


void httpd_setup()
{
    SPIFFS.begin();
    httpd.serveStatic("/", SPIFFS, "/index.html");
    httpd.begin();
}


void httpd_loop()
{
    httpd.handleClient();
}