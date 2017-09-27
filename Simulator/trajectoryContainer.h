#pragma once

#include "trajectoryReader.h"
#include "CoordinateFrameHandler.h"

#include "Rinex3ObsData.hpp"
#include "Rinex3NavData.hpp"
#include "RinexSatID.hpp"
#include "GPSEphemerisStore.hpp"
#include "Xvt.hpp"

using namespace gpstk;


typedef struct {
	Xvt xvt;
	double pseudorange;
	GPSEphemeris ephemeris;
} mTrajectoryData;
typedef std::map<SatID, std::map<CivilTime, mTrajectoryData>> gps_eph_map;


class trajectoryContainer {

public:
	trajectoryContainer();
	~trajectoryContainer();

	void addObsData();
	void addNavData(const GPSEphemeris& gpseph);
	void assembleTrajectories(SatID,CivilTime,Xvt);		//Store data in containers

	CivilTime listEpochs();			//Print all stored Epochs
	CivilTime listEpochs(SatID);	//Print all stored epochs for a specified sat

	gps_eph_map getNavData();
	GPSEphemeris getNavData(SatID);
	GPSEphemeris getNavData(CivilTime);
	GPSEphemeris getNavData(SatID, CivilTime);


private:
	
	GPSEphemerisStore ephemerisStore;
	GPSEphemeris ephemeris;
	RinexSatID sat;
	//trajectoryData_c trajectoryData;
	gps_eph_map trajectoryDataContainer;;
	mTrajectoryData trajectoryData;
	


};

class trajectoryData_c {
public:
	trajectoryData_c();
	~trajectoryData_c();

	void setData();	//
	void getData();

	void setxvt();

private:
	mTrajectoryData trajData;

};
