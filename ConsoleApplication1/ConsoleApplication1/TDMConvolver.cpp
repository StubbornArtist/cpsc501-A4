#include "stdafx.h"
#include "Convolver.cpp"

class TDMConvolver : public Convolver{


	public: 
		AudioFile convolve(AudioFile sound1, AudioFile sound2) {
			return *(new AudioFile());
		}
};