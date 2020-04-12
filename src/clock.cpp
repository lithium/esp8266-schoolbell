#include "clock.h"

static WiFiUDP ntpUdp;
static NTPClient ntpClient(ntpUdp, CONFIG_NTP_SERVER, CONFIG_NTP_UTC_OFFSET_SECONDS, CONFIG_NTP_UPDATE_INTERVAL);

void clock_setup()
{
	ntpClient.begin();

}

void clock_loop()
{
	ntpClient.update();

}
