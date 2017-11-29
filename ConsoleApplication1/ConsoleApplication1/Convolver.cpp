#include "stdafx.h"
#include "AudioFile.cpp"

class Convolver {

	public:
		AudioFile virtual convolve(AudioFile sound, AudioFile IRsound);
};