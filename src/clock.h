#ifndef CLOCK_H_
#define CLOCK_H_

#include <NTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include "config.h"

void clock_setup();
void clock_loop();
void ring_tone(unsigned int freq, unsigned long duration);
#endif