#ifndef AUDIO_H_
#define AUDIO_H_
#include "config.h"
#include <SD.h>
#include <ESP8266HTTPClient.h>
#include "AudioFileSourceSPIFFS.h"
#include "AudioOutputI2SNoDAC.h"
#include "AudioGeneratorWAV.h"

void audio_setup();
void audio_loop();
void audio_ring();
#endif