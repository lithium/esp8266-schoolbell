#include "settings.h"
#include <EEPROM.h>

BellSettings _activeSettings;


void settings_setup()
{
	_activeSettings.load();
}

BellSettings &BellSettings::active() {
	return _activeSettings;
}


void BellSettings::load() {
	EEPROM.begin(EEPROM_FULL_SIZE);
	uint8_t cookie = EEPROM.read(EEPROM_ADDR_MAGIC);
	if (cookie == EEPROM_MAGIC_COOKIE) {
		// cookie present, assume valid saved data 
		EEPROM.get(EEPROM_ADDR_SETTINGS, _activeSettings);
	}
}
void BellSettings::save() {
	EEPROM.put(EEPROM_ADDR_SETTINGS, _activeSettings);
	EEPROM.write(EEPROM_ADDR_MAGIC, EEPROM_MAGIC_COOKIE);
	EEPROM.commit();
}