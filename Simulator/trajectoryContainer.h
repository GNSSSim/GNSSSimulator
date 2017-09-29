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
//TODO: ^^^^ DELETE THESE ^^^^

// v2 map
typedef std::map<SatID, std::map<CivilTime, double>> PseudoRangeContainer;


class satDataContainer {

public:
	satDataContainer();
	~satDataContainer();

	/* Add these items to the gps_eph_map container */
	void assembleTrajectories(SatID,CivilTime,Xvt,double);		//Store data in containers

	/* When reading in RINEX line by line, pass the pseudorange for each epoch 
		for each Satellite
	*/
	void assemblePseudoRangeContainer(SatID, CivilTime, double);
	
	/* Pass EphemerisStore reference to SatDataContainer.
		EphStore stores all the ephemeris data for each satellite.
	*/
	void passEphemerisStore(GPSEphemerisStore&);

	/* Get the full epoch list for a given satellite
		@Param The SatID object
		@return The <vector> containing all the epoch times for the given SatID
	*/
	std::vector<CivilTime> getEpochVectorforSat(SatID&);

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

	/* Create a CivilianTime object from input time as arguments
	*/
	CivilTime getCivilTimeObject(int year, int month, int day, int hour, int minute, int second);
	
	/* Query Ephemeris Data for a [SatID, CivilianTime] combination
		Time can be any valid CivilianTime object. If Navigation Data
		from RINEX file for the queried epoch is not available,
		GPSTK uses built-in models to calculate Satellite position.
	*/
	OrbitEph getSatInfoAtEpoch(SatID, CivilTime);
private:
	
	GPSEphemerisStore ephemerisStore;
	GPSEphemeris ephemeris;
	RinexSatID sat;
	/* Contains the C1 Pseudorange for every RINEX epoch for each satellite
	*/
	PseudoRangeContainer pseudoRangeContainer;
	
	
	mTrajectoryData trajectoryData;
	gps_eph_map trajectoryDataContainer;


};

