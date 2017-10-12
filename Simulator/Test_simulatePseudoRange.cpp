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

	string ephFilewPath = "..\\Simulator\\RinexFiles\\brdc1820.17n"; // "..\\Simulator\\RinexFiles\\brdc1810.17n"; // "..\\Simulator\\RinexFiles\\brdc1820.17n";
	RinexNavStream rnffs(ephFilewPath.c_str());    // Open ephemerides data file

	rnffs.open(ephFilewPath.c_str(), ios::in);

	if (!rnffs.is_open() || !rnffs.is_open()) {
		LOG(WARNING) << "Warning : could not open file ";
		return;
	}

	RinexNavData rne;
	RinexNavHeader hdr;
	GPSEphemerisStore bcestore;
	SatID myID(1 , SatID::SatelliteSystem::systemGPS);
	
	CommonTime civtime;

	gpstk::GPSWeekSecond gpsTime;
	gpsTime.week = 1955; // 1955 // 931
	gpsTime.sow = 518400+532; // 432000 // 432000+86400 = 518400

	rnffs >> hdr;

	//hdr.dump(cout);
	int loop = 0;
	// Storing the ephemeris in "bcstore"
	while (rnffs >> rne) {		
		try {
			bcestore.addEphemeris(rne);
			loop += 1;
		}catch (...) {
			cout << loop << endl;
			cout << "This eph data caused an error" << endl << endl;
			//rne.dump(cout);
			loop += 1;
		}
	}
	
	// Setting the criteria for looking up ephemeris
	//bcestore.SearchNear();

	/*for (size_t i = 1; i < 32; i++) {

		myID.id = i;
		try {

			Xvt xvt_data = bcestore.getXvt(myID, gpsTime);
			cout << "Sat Id: " << myID.id << endl;
			cout << xvt_data << endl << endl;

		}
		catch (...)
		{
			cout << "Error. Probably we did not find the satId." << endl;
		}
	}*/

	gnsssimulator::TrajectoryStream trajFileIn("..\\Simulator\\TrajectoryFiles\\SimpleTraj_1955_518400-518404.txt");
	gnsssimulator::TrajectoryStream trajFileOut("..\\Simulator\\TrajectoryFiles\\SimpleTraj_1955_518400-518404__Out.txt", std::ios::out);
	gnsssimulator::TrajectoryHeader trajHeader;
	gnsssimulator::TrajectoryData trajData;
	gnsssimulator::TrajectoryData testPos;
	trajFileIn >> trajHeader;
	trajFileOut << trajHeader;

	gnsssimulator::TrajectoryStore TrajStore;
	cout << "Next epoch" << endl;
	while (trajFileIn >> trajData) {
		TrajStore.addPosition(trajData);
		testPos = TrajStore.findPosition(trajData.gpsTime);

		cout << endl << "Next epoch" << endl;
		trajFileOut << trajData;
		cout << testPos;
	}

	trajFileIn.close();
	trajFileOut.close();


}
