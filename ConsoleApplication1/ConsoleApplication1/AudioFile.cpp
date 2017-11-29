#include "stdafx.h"
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
			unsigned short bitsPerSample;
			unsigned char subChunk2Id[4];
			unsigned int subChunk2Size;
			unsigned char * data;

	public:

		void fromFile(char * path) {
			FILE * fp = fopen(path, "rb");

			fread(chunkId, sizeof(unsigned char), 4, fp);
			fread(&chunkSize, sizeof(unsigned int), 1, fp);
			fread(format, sizeof(unsigned char), 4, fp);
			fread(subChunk1Id, sizeof(unsigned char), 4, fp);
			fread(&subChunk1Size, sizeof(unsigned int), 1, fp);
			fread(&audioFormat, sizeof(unsigned short), 1, fp);
			fread(&numChannels, sizeof(unsigned short), 1, fp);
			fread(&sampleRate, sizeof(unsigned int), 1, fp);
			fread(&byteRate, sizeof(unsigned int), 1, fp);
			fread(&blockAlign, sizeof(unsigned short), 1, fp);
			fread(&bitsPerSample, sizeof(unsigned short), 1, fp);
			fread(&subChunk2Id, sizeof(unsigned char), 4, fp);
			fread(&subChunk2Size, sizeof(unsigned int), 1, fp);

			data = new unsigned char[subChunk2Size];
			fread(data, sizeof(unsigned char), subChunk2Size, fp);
			fclose(fp);
		}

		void toFile(char * path) {
			FILE * fp = fopen(path, "wb");

			fwrite(chunkId, sizeof(char), 4, fp);
			fwrite(&chunkSize, sizeof(int), 1, fp);
			fwrite(format, sizeof(char), 4, fp);
			fwrite(subChunk1Id, sizeof(char), 4, fp);
			fwrite(&subChunk1Size, sizeof(int), 1, fp);
			fwrite(&audioFormat, sizeof(short), 1, fp);
			fwrite(&numChannels, sizeof(short), 1, fp);
			fwrite(&sampleRate, sizeof(int), 1, fp);
			fwrite(&byteRate, sizeof(int), 1, fp);
			fwrite(&blockAlign, sizeof(short), 1, fp);
			fwrite(&bitsPerSample, sizeof(short), 1, fp);
			fwrite(&subChunk2Id, sizeof(char), 4, fp);
			fwrite(&subChunk2Size, sizeof(int), 1, fp);
			
			fwrite(data, sizeof(char), subChunk2Size, fp);
			fclose(fp);
		}


	
};