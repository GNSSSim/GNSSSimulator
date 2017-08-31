#pragma once
#include <fstream>
#include <string>
#include <iostream>
#include "GNSStime.h"
#include "CoordinateFrames.h"
class trajectoryReader
{


public:
	trajectoryReader();
	trajectoryReader(char*);
	~trajectoryReader();

	void open(void);
	void close(void);
	bool is_open();
	std::string readLine(void);
	bool isFormatValid(void);
	GPSTime nextTime(void);
	std::string readHeader();
	void setFile2Begining(void);
	LLHCoordinate nextLLH(void);
	ECEFCoordinate nextECEF(void);

private:
	void nextPos(double*, double*, double*);
	bool isNotHeaderRead = true;
	bool isFileOpen = false;
	char* fileNamewPath;
	std::ifstream trajFile;
};

