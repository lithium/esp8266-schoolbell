#ifndef SETTINGS_H_
#define SETTINGS_H_

#define NUM_PERIODS 6

typedef struct period {
	int start; // minutes from midnight
	int end;
} period_t;

class BellSettings {
public:
	unsigned int bellFrequency = 110;
	unsigned long bellDurationMs = 1800;
	long gmtOffsetHours = -8;
	long ntpIntervalMs = 30*60000;
	period_t bellSchedule[NUM_PERIODS];

	static BellSettings &active();

	void load();
	void save();
};

#define EEPROM_ADDR_MAGIC 0
#define EEPROM_MAGIC_SIZE 1
#define EEPROM_MAGIC_COOKIE 0b11111001

#define EEPROM_ADDR_SETTINGS EEPROM_ADDR_MAGIC+EEPROM_MAGIC_SIZE
#define EEPROM_SETTINGS_SIZE sizeof(BellSettings)

#define EEPROM_FULL_SIZE EEPROM_ADDR_SETTINGS+EEPROM_SETTINGS_SIZE

void settings_setup();
#endif
