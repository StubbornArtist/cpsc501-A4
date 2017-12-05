#include "stdafx.h"
#include <vector>

#define RIFF "RIFF"
#define WAVE "WAVE"
#define FMT "fmt "
#define DATA "data"
using namespace std;


class AudioFile {
	private:
			unsigned char chunkId[4];
			unsigned int chunkSize;
			unsigned char format[4];
			unsigned char subChunk1Id[4];
			unsigned int subChunk1Size;
			unsigned short audioFormat;
			unsigned short numChannels;
			unsigned int sampleRate;
			unsigned int byteRate;
			unsigned short blockAlign;
			unsigned int bitsPerSample;
			unsigned char subChunk2Id[4];
			unsigned int subChunk2Size;
			vector<double> data;
			int numSamples;
			int bytesPerSample;

			double convertSample(int16_t sample) {
				return ((double)sample) / 32767.0;
			}

			int16_t convertSampleBack(double sample) {
				return (int16_t)(sample * 32767.0);
			}

	public:

		void fromFile(char * path) {
			FILE * fp;
			fopen_s(&fp, path, "rb");

			fread(chunkId, 1, 4, fp);
			fread(&chunkSize, 4, 1, fp);
			fread(format, 1, 4, fp);
			fread(subChunk1Id, 1, 4, fp);
			fread(&subChunk1Size, 4, 1, fp);
			fread(&audioFormat, 2, 1, fp);
			fread(&numChannels, 2, 1, fp);
			fread(&sampleRate, 4, 1, fp);
			fread(&byteRate, 4, 1, fp);
			fread(&blockAlign, 2, 1, fp);
			fread(&bitsPerSample, 4, 1, fp);
			fread(subChunk2Id, 1, 4, fp);
			fread(&subChunk2Size, 4, 1, fp);

			bytesPerSample = bitsPerSample / 8;
			numSamples = subChunk2Size / (numChannels * bytesPerSample);
			data = vector<double>();
			for (int i = 0; i < numSamples; i++) {
				int16_t buf;
				fread(&buf, bytesPerSample, 1, fp);
				data.push_back(convertSample(buf));
			}
			
			fclose(fp);
		}

		void toFile(char * path) {
			FILE * fp;
			fopen_s(&fp, path, "wb");

			fwrite(chunkId, 1, 4, fp);
			fwrite(&chunkSize, 4, 1, fp);
			fwrite(format, 1, 4, fp);
			fwrite(subChunk1Id, 1, 4, fp);
			fwrite(&subChunk1Size, 4, 1, fp);
			fwrite(&audioFormat, 2, 1, fp);
			fwrite(&numChannels, 2, 1, fp);
			fwrite(&sampleRate, 4, 1, fp);
			fwrite(&byteRate, 4, 1, fp);
			fwrite(&blockAlign, 2, 1, fp);
			fwrite(&bitsPerSample, 4, 1, fp);
			fwrite(subChunk2Id, 1, 4, fp);
			fwrite(&subChunk2Size, 4, 1, fp);
			
			for (int i = 0; i < numSamples; i++) {
				int16_t res = convertSampleBack(data.at(i));
				fwrite(&res, bytesPerSample, 1, fp);
			}
			fclose(fp);
        }

		void create (int bitsPerSample, int numChannel, int sampleRate, vector<double>data) {
			memcpy(chunkId, RIFF, 4);
			memcpy(format, WAVE, 4);
			memcpy(subChunk1Id, FMT, 4);
			memcpy(subChunk2Id, DATA, 4);
			subChunk1Size = 18;
			audioFormat = 1;

			this->numChannels = (short)numChannel;
			this->bitsPerSample = bitsPerSample;
			this->sampleRate = sampleRate;
			this->numSamples = data.size();
			this->data = data;

			bytesPerSample = bitsPerSample / 8;
			subChunk2Size = numChannels * numSamples * bytesPerSample;
			chunkSize = 36 + subChunk2Size;
			blockAlign = (short)(numChannels * bytesPerSample);
			byteRate = (int)ceil(sampleRate * blockAlign);
		}

		 vector<double> getData() {
			 return data;
		}

		 int getNumSamples() {
			 return numSamples;
		 }
};