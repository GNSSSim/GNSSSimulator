#pragma once

#include "trajectoryReader.h"
#include "CoordinateFrameHandler.h"

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>

#include "Rinex3ObsData.hpp"
#include "Rinex3NavData.hpp"
#include "RinexSatID.hpp"
#include "GPSEphemerisStore.hpp"
#include "Xvt.hpp"
#include "GPSWeek.hpp"
#include "GPSWeekZcount.hpp"
#include "GPSWeekSecond.hpp"

using namespace gpstk;

// v1 struct and map
typedef struct {
	Xvt xvt;
	double pseudorange;
	GPSEphemeris ephemeris;
} mTrajectoryData;
typedef std::map<SatID, std::map<CivilTime, mTrajectoryData>> gps_eph_map;

// v2 struct and map
typedef struct {
	double pseudoRange;
	std::vector<CivilTime> timeVector;
};


class trajectoryContainer {

public:
	trajectoryContainer();
	~trajectoryContainer();

	void addObsData();
	/* Add these items to the gps_eph_map container */
	void assembleTrajectories(SatID,CivilTime,Xvt,double);		//Store data in containers
	void assembleEphemerisStore(GPSEphemerisStore&);

	CivilTime listEpochs();			//Print all stored Epochs
	CivilTime listEpochs(SatID);	//Print all stored epochs for a specified sat
	

	void write_to_cout_all();		//Write to trajectory format(One file per sat)
	void write_to_cout_test(SatID,CivilTime);

	/* Check if a given epoch is outside of the associated epoch observation vector
	* Returns TRUE if satellite is not observable in the given epoch.
	* @param : CivilianTime in question
	* @param : Time vectors of the given sat.
	*/
	bool isEpochonDarkSide(CivilTime civiliantime, std::vector<CivilTime>& referenceEpochs);
	
	/* Get Satellite ID object
	* Satellites are ordered and stored inside the DataContainer object.
	* This function iterates through it and returns the ith satellite stored.
	*/
	SatID getSatIDObject(int, SatID::SatelliteSystem );


	CivilTime getCivilTimeObject(int year, int month, int day, int hour, int minute, int second);
	
	
	GPSEphemeris getSatInfoAtEpoch(SatID, CivilTime);
private:
	
	GPSEphemerisStore ephemerisStore;
	GPSEphemeris ephemeris;
	RinexSatID sat;
	//trajectoryData_c trajectoryData;
	gps_eph_map trajectoryDataContainer;;
	mTrajectoryData trajectoryData;
	


};

