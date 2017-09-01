#pragma once
#include <fstream>
#include <string>
#include <iostream>
#include "GNSStime.h"
#include "CoordinateFrames.h"

#define TESTING

class trajectoryReader
{


public:
	trajectoryReader();
	trajectoryReader(char*);
	~trajectoryReader();

	void open(void);
	void close(void);
	GPSTime nextTime(void);
	

#ifdef TESTING

public:

#else

private:

#endif
	LLHCoordinate nextLLH(void);
	ECEFCoordinate nextECEF(void);
	bool isFormatValid(void);
	bool is_open();
	void setFile2Begining(void);
	std::string readHeader();
	std::string readLine(void);

private:
	void nextPos(double*, double*, double*);
	bool isNotHeaderRead = true;
	bool isFileOpen = false;
	char* fileNamewPath;
	std::ifstream trajFile;
};

