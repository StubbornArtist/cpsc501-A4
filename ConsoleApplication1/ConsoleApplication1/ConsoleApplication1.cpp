// ConsoleApplication1.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "TDMConvolver.cpp"
#include "FDMConvolver.cpp"
#include "AudioFile.cpp"
#include <algorithm>

#define NUM_CHANNELS 1
#define SAMPLE_RATE 44100
#define BITS_PER_SAMPLE 16

using namespace std;

vector<double> scale(vector<double> array , double scaleFactor);
double abs_val(double val);
double abs_max(vector<double> array);

int main(int argc, char * argv[])
{
	AudioFile file1;
	AudioFile file2;
	AudioFile output;
	FDMConvolver convolver;

	if (argc < 4) {
		throw "Three arguments required, you only provided " + argc ;
		throw "Please enter : <inputfile> <IRFile> <outputfile>";
	}

	file1.fromFile(argv[1]);
	file2.fromFile(argv[2]);

	int file1NumSamp = file1.getNumSamples();
	int file2NumSamp = file2.getNumSamples();
	int numSamples = (file1NumSamp + file2NumSamp - 1);

	vector<double> result = convolver.convolve(file1.getData(),file2.getData());
	double max = abs_max(result);
	result = scale(result, (1.0/max));

	output.create(BITS_PER_SAMPLE, NUM_CHANNELS, SAMPLE_RATE, result);
	output.toFile(argv[3]);
}

vector<double> scale(vector<double> array, double scaleFactor) {
	vector<double> result = vector<double>();
	for (int i = 0; i < array.size() ; i++) {
		result.push_back(array[i] * scaleFactor);
	}
	return result;
}

double abs_max(vector<double> array) {
	double max = 0.0;
	for (int i = 0; i < array.size(); i++) {
		double val = abs_val(array[i]);
		if (val > max) max = val;
	}

	return max;
}
double abs_val(double val) {

	if (val < 0) {
		return val * -1;
	}
	return val;
}



