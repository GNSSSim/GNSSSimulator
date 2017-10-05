#include "stdafx.h"
#include "TrajectoryHeader.hpp"
#include "TrajectoryData.hpp"
#include "TrajectoryStream.hpp"
#include "RinexNavData.hpp"
#include "TrajectoryStore.hpp"

#include "Test_simulatePseudoRange.hpp"

using namespace gpstk::StringUtils;
using namespace std;
using namespace gpstk;
using namespace gnsssimulator;

void makeSimplePseudoRange(void) {

	string ephFilewPath = "..\\Simulator\\RinexFiles\\brdc1810.17n";
	Rinex3NavStream rnffs(ephFilewPath.c_str());    // Open ephemerides data file

	rnffs.open(ephFilewPath.c_str(), ios::in);

	if (!rnffs.is_open() || !rnffs.is_open()) {
		LOG(WARNING) << "Warning : could not open file ";
		return;
	}

	Rinex3NavData rne;
	Rinex3NavHeader hdr;
	GPSEphemerisStore bcestore;
	SatID myID(1 , SatID::SatelliteSystem::systemGPS);
	
	CommonTime civtime;

	gpstk::GPSWeekSecond gpsTime;
	gpsTime.week = 1955;
	gpsTime.sow = 432000;

	rnffs >> hdr;

	hdr.dump(cout);

	// Storing the ephemeris in "bcstore"
	while (rnffs >> rne) bcestore.addEphemeris(rne);

	// Setting the criteria for looking up ephemeris
	//bcestore.SearchNear();

	for (size_t i = 1; i < 32; i++) {

		myID.id = i;
		try {

			Xvt xvt_data = bcestore.getXvt(myID, gpsTime);
			cout << xvt_data << endl;

		}
		catch (...)
		{
			cout << "Error. Probably we did not find the satId." << endl;
		}
	}
}
