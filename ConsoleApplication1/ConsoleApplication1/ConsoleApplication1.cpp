// ConsoleApplication1.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "TDMConvolver.cpp"

int main(int argc, char * argv[])
{
	AudioFile file1;
	AudioFile file2;

	if (argc < 4) {
		throw "Three arguments required, you only provided " + argc ;
		throw "Please enter : <inputfile> <IRFile> <outputfile>";
	}

	file1.fromFile(argv[1]);
	file2.fromFile(argv[2]);


}

