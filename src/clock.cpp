#include "clock.h"
#include "settings.h"

static WiFiUDP ntpUdp;
static NTPClient ntpClient(ntpUdp, CONFIG_NTP_SERVER, CONFIG_NTP_UTC_OFFSET_SECONDS, CONFIG_NTP_UPDATE_INTERVAL);

void clock_setup()
{
	ntpClient.begin();

	pinMode(LED_BUILTIN, OUTPUT);
	digitalWrite(LED_BUILTIN, 1);
}


void ring_bell(int bell_id, BellSettings &settings)
{
	static int _last_bell = -1;

	if (_last_bell != bell_id) {
		_last_bell = bell_id;
		Serial.print("RING ");
		Serial.println(bell_id);

		tone(SPEAKER_PIN, settings.bellFrequency, settings.bellDurationMs);
		digitalWrite(LED_BUILTIN, 0);
		delay(settings.bellDurationMs);
		digitalWrite(LED_BUILTIN, 1);
	}
}

void clock_loop()
{
	ntpClient.update();
	int day = ntpClient.getDay();

	if (day == 0 || day == 6) {
		// skip weekends
		return;
	}

	BellSettings &settings = BellSettings::active();
	int now = (ntpClient.getHours()+1)*60 + ntpClient.getMinutes();

	for (int i=0; i < NUM_PERIODS; i++) {
		if (now == settings.bellSchedule[i].start) {
			ring_bell(i*2, settings);
			break;
		}
		else if (now == settings.bellSchedule[i].end) {
			ring_bell(i*2+1, settings);
			break;
		}
	}
}
