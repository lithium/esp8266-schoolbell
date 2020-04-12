#ifndef HTTP_SERVER_H
#define HTTP_SERVER_H

#include <ESP8266WebServer.h>

extern ESP8266WebServer httpd;

void httpd_setup();
void httpd_loop();

#endif
