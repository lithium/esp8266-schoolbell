#include "audio.h"



static AudioFileSourceSPIFFS *source = NULL;
static AudioOutputI2SNoDAC *out = NULL;
static AudioGeneratorWAV *decoder = NULL;


void audio_setup()
{
	out = new AudioOutputI2SNoDAC();
	digitalWrite(LED_PIN, LOW);
	pinMode(LED_PIN, OUTPUT);
}

void audio_ring()
{
	source = new AudioFileSourceSPIFFS("/bell.wav");
	decoder = new AudioGeneratorWAV();
	decoder->begin(source, out);
	digitalWrite(LED_PIN, LOW);
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
			digitalWrite(LED_PIN, HIGH);
		}
	}
}
