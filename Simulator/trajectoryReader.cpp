#include "stdafx.h"
#include "trajectoryReader.h"

//using namespace std;
trajectoryReader::trajectoryReader(){
	this->fileNamewPath = "This_File_is_not_exist_and_should_not_be_exist_424242_69696969_21212121";
	this->trajFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
}

trajectoryReader::trajectoryReader(char* fileNamewPath){
	this->fileNamewPath = fileNamewPath;
	this->trajFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
}

trajectoryReader::~trajectoryReader()
{
}

void trajectoryReader::open(void){
	try{
		this->trajFile.open(this->fileNamewPath);
		this->isFileOpen = true;
	}
	catch(...){
		this->isFileOpen = false;
	}

}

void trajectoryReader::close(void){
	try{
		this->trajFile.close();
		this->isFileOpen = false;
	}
	catch (...){
		this->isFileOpen = true;
	}
}

bool trajectoryReader::is_open(void){
	return this->isFileOpen;
}

std::string trajectoryReader::readLine(void){

	std::string line;
	std::getline(this->trajFile, line);
	return line;
}


bool trajectoryReader::isFormatValid(void){

	bool isValidForm = true;

	std::string delimiter = " ";
	std::string firstLine = this->readHeader();
	std::string token;
	size_t pos = 0;
	pos = firstLine.find(delimiter);
	token = firstLine.substr(0, pos);
	if (token.compare("WN") != 0){
		isValidForm = false;
	}
	firstLine.erase(0, pos + delimiter.length());

	pos = firstLine.find(delimiter);
	token = firstLine.substr(0, pos);
	if (token.compare("ToW") != 0){
		isValidForm = false;
	}
	firstLine.erase(0, pos + delimiter.length());

	delimiter = "\n";
	pos = firstLine.find(delimiter);
	token = firstLine.substr(0, pos);
	if (token.compare("LLH") !=0  && token.compare("ECEF") != 0){
		isValidForm = false;
	}
	firstLine.erase(0, pos + delimiter.length());

	this->setFile2Begining();
	this->isNotHeaderRead = true;

	return isValidForm;
}

std::string trajectoryReader::readHeader(){

	this->setFile2Begining();
	std::string header = this->readLine();

	this->isNotHeaderRead = false;
	return header;
}

void trajectoryReader::setFile2Begining(void){
	this->trajFile.clear();
	this->trajFile.seekg(0, std::ios::beg);
}

GPSTime trajectoryReader::nextTime(void){

	GPSTime time;
	time.WN = 0;
	time.ToW = 0;

	if (this->isNotHeaderRead){
		this->readHeader();
	}

	std::string line = this->readLine();

	std::string delimiter = " ";
	std::string token;
	size_t pos = 0;
	pos = line.find(delimiter);
	token = line.substr(0, pos);
	line.erase(0, pos + delimiter.length());

	time.WN = std::stoi(token);
	
	pos = line.find(delimiter);
	token = line.substr(0, pos);
	line.erase(0, pos + delimiter.length());
	
	time.ToW = std::stoi(token);

	return time;
}

void trajectoryReader::nextPos(double* coor1, double* coor2, double* coor3){

	if (this->isNotHeaderRead){
		this->readHeader();
	}
	std::string line = this->readLine();

	std::string delimiter = " ";
	std::string token;
	size_t linePos = 0;

	linePos = line.find(delimiter);
	line.erase(0, linePos + delimiter.length());
	linePos = line.find(delimiter);
	line.erase(0, linePos + delimiter.length());

	linePos = line.find(delimiter);
	token = line.substr(0, linePos);
	line.erase(0, linePos + delimiter.length());

	*coor1 = std::stoi(token);

	linePos = line.find(delimiter);
	token = line.substr(0, linePos);
	line.erase(0, linePos + delimiter.length());

	*coor2 = std::stoi(token);
	
	linePos = line.find(delimiter);
	token = line.substr(0, linePos);
	line.erase(0, linePos + delimiter.length());

	*coor3 = std::stoi(token);
}

LLHCoordinate trajectoryReader::nextLLH(void){

	LLHCoordinate pos;
	pos.latidute = 0;
	pos.longitude = 0;
	pos.height = 0;

	this->nextPos(&pos.latidute, &pos.longitude, &pos.height);

	return pos;
}

ECEFCoordinate trajectoryReader::nextECEF(void){

	ECEFCoordinate pos;
	pos.x = 0;
	pos.y = 0;
	pos.z = 0;

	this->nextPos(&pos.x, &pos.y, &pos.z);

	return pos;

}