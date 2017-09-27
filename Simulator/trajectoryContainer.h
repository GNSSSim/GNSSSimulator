#pragma once

#include "trajectoryReader.h"

#include "Rinex3ObsData.hpp"
#include "Rinex3NavData.hpp"
#include "RinexSatID.hpp"
#include "GPSEphemerisStore.hpp"
#include "Xvt.hpp"

using namespace gpstk;

class trajectoryContainer {

public:
	trajectoryContainer();
	~trajectoryContainer();

	void addObsData();
	void addNavData(const GPSEphemeris& gpseph);

private:
	GPSEphemerisStore ephemerisStore;


};