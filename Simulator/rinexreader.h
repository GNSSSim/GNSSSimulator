#pragma once

#include "RinexObsBase.hpp"
#include "RinexObsHeader.hpp"
#include "RinexObsData.hpp"
#include "RinexObsStream.hpp"
#include "RinexDatum.hpp"
#include "CivilTime.hpp"
#include "GNSSconstants.hpp"


class RinexReader {

public:
	RinexReader();
	~RinexReader();

	void setInputFile(char*);
	void setOutputFile(char*);
private:
	char* inputpath;
	char* outputpath;


};