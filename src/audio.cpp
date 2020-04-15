#include "audio.h"

#include <SD.h>
#include <ESP8266HTTPClient.h>
#include "AudioFileSourceSPIFFS.h"
#include "AudioOutputI2SNoDAC.h"
#include "AudioGeneratorWAV.h"


static AudioFileSourceSPIFFS *source = NULL;
static AudioOutputI2SNoDAC *out = NULL;
static AudioGeneratorWAV *decoder = NULL;

void audio_setup()
{
	out = new AudioOutputI2SNoDAC();
}

void audio_ring()
{
	source = new AudioFileSourceSPIFFS("/bell.wav");
	decoder = new AudioGeneratorWAV();
	decoder->begin(source, out);
}

void audio_loop()
{
	if (decoder != NULL && decoder->isRunning()) {
		if (!decoder->loop()) {
			decoder->stop();
			source->close();
			delete source;
			delete decoder;
			source = NULL;
			decoder = NULL;
		}
	}
}
