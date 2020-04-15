#include "http_server.h"
#include <ArduinoJson.h>
#include "settings.h"
#include "clock.h"

ESP8266WebServer httpd;


void handleGetConfig() {
    httpd.sendHeader("Access-Control-Allow-Origin", "*");

	BellSettings &settings = BellSettings::active();
	StaticJsonDocument<512> doc;

    JsonArray schedule = doc.createNestedArray("bellSchedule");
    for (int i=0; i < NUM_PERIODS; i++) {
    	JsonArray row = schedule.createNestedArray();
    	row.add(settings.bellSchedule[i].start);
    	row.add(settings.bellSchedule[i].end);
    }

    doc["bellFrequency"] = settings.bellFrequency;
    doc["bellDurationMs"] = settings.bellDurationMs;
    doc["gmtOffsetHours"] = settings.gmtOffsetHours;
    doc["ntpIntervalMs"] = settings.ntpIntervalMs;
    doc["useZeroPeriod"] = settings.useZeroPeriod;

	String buf;
	serializeJson(doc, buf);
	httpd.send(200, "application/json", buf);
}

void handlePostTest() {
    httpd.sendHeader("Access-Control-Allow-Origin", "*");

	StaticJsonDocument<512> doc;
	String body = httpd.arg("plain");
	deserializeJson(doc, body);
	BellSettings &settings = BellSettings::active();
	unsigned int freq = settings.bellFrequency;
	unsigned long duration = settings.bellDurationMs;
	if (doc.containsKey("bellFrequency")) {
		freq = doc["bellFrequency"];
	}
	if (doc.containsKey("bellDurationMs")) {
		duration = doc["bellDurationMs"];
	}
	ring_tone(freq, duration);
    httpd.send(200, "application/json", "true");
}
void handlePostConfig() {
    httpd.sendHeader("Access-Control-Allow-Origin", "*");

	StaticJsonDocument<512> doc;
	String body = httpd.arg("plain");
	deserializeJson(doc, body);

	BellSettings &settings = BellSettings::active();
	if (doc.containsKey("bellFrequency")) {
		settings.bellFrequency = doc["bellFrequency"];
	}
	if (doc.containsKey("bellDurationMs")) {
		settings.bellDurationMs = doc["bellDurationMs"];
	}
	if (doc.containsKey("gmtOffsetHours")) {
		settings.gmtOffsetHours = doc["gmtOffsetHours"];
	}
	if (doc.containsKey("ntpIntervalMs")) {
		settings.ntpIntervalMs = doc["ntpIntervalMs"];
	}
	if (doc.containsKey("useZeroPeriod")) {
		settings.useZeroPeriod = doc["useZeroPeriod"];
	}
	if (doc.containsKey("bellSchedule")) {
		JsonArray schedule = doc["bellSchedule"];
		for (int i=0; i < NUM_PERIODS; i++) {
			JsonArray row = schedule[i];
			settings.bellSchedule[i].start = row[0];
			settings.bellSchedule[i].end = row[1];
		}
	}
	settings.save();
    httpd.send(200, "application/json", "true");
}

void httpd_setup()
{
    SPIFFS.begin();
    httpd.serveStatic("/", SPIFFS, "/index.html");
    httpd.on("/config", HTTP_GET, handleGetConfig);
    httpd.on("/config", HTTP_POST, handlePostConfig);

    httpd.on("/test", HTTP_POST, handlePostTest);


    httpd.begin();
}


void httpd_loop()
{
    httpd.handleClient();
}