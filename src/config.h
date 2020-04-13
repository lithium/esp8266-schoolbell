#ifndef CONFIG_H
#define CONFIG_H

#define CONFIG_WIFI_HOSTNAME "schoolbell"

#define CONFIG_OTA_PORT 8266
#define CONFIG_OTA_HOSTNAME CONFIG_WIFI_HOSTNAME
#undef CONFIG_OTA_PASSWORD


#define SPEAKER_PIN D5


#define CONFIG_NTP_SERVER "pool.ntp.org"
#define CONFIG_NTP_UTC_OFFSET_SECONDS -8*60*60
#define CONFIG_NTP_UPDATE_INTERVAL 60000

#include "config_local.h"



#endif