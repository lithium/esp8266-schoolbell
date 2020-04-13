#include "http_server.h"
#include <ArduinoJson.h>
#include "settings.h"

ESP8266WebServer httpd;


void handleGetConfig() {
	BellSettings &settings = BellSettings::active();
	StaticJsonDocument<512> doc;

    JsonArray schedule = doc.createNestedArray("schedule");
    for (int i=0; i < NUM_PERIODS; i++) {
    	JsonArray row = schedule.createNestedArray();
    	row.add(settings.bellSchedule[i].start);
    	row.add(settings.bellSchedule[i].end);
    }

    doc["bellFrequency"] = settings.bellFrequency;
    doc["bellDurationMs"] = settings.bellDurationMs;
    doc["gmtOffsetHours"] = settings.gmtOffsetHours;
    doc["ntpIntervalMs"] = settings.ntpIntervalMs;

	String buf;
	serializeJson(doc, buf);
	httpd.send(200, "application/json", buf);
}

void handlePostConfig() {
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


    httpd.begin();
}


void httpd_loop()
{
    httpd.handleClient();
}