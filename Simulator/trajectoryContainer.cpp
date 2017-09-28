#include "stdafx.h"
#include "trajectoryContainer.h"

trajectoryContainer::trajectoryContainer()
{
}

trajectoryContainer::~trajectoryContainer()
{
}


void trajectoryContainer::addNavData(const GPSEphemeris& gpseph)
{
	ephemerisStore.addEphemeris(gpseph);
}

void trajectoryContainer::assembleTrajectories(SatID sat,CivilTime civtime, Xvt xvt_i, double pseudorange)
{
	trajectoryData.xvt = xvt_i;
	trajectoryData.pseudorange = pseudorange;
	trajectoryDataContainer[sat][civtime] = trajectoryData;
	

}


void trajectoryContainer::write_to_cout_all()
{
	gps_eph_map::const_iterator it;
	std::map<CivilTime, mTrajectoryData>::const_iterator kt;
	mTrajectoryData outputData;

	CivilTime time;
	GPSWeekSecond gpswns;
	ECEFCoordinate ecefcoords;
	

	for (it = trajectoryDataContainer.begin(); it != trajectoryDataContainer.end(); it++) {
		std::cout << (*it).first << std::endl;
		for (kt = (*it).second.begin(); kt != (*it).second.end(); kt++) {
			//Get WN and ToW
			time = (*kt).first;							
			time = time.convertToCommonTime();
			gpswns.convertFromCommonTime(time);
			//Get Position Data
			outputData = (*kt).second;

			ecefcoords.x = outputData.xvt.x[0];
			ecefcoords.y = outputData.xvt.x[1];
			ecefcoords.z = outputData.xvt.x[2];
			

			std::cout << gpswns.getWeek() << " " << gpswns.getSOW() << " " << ecefcoords.x << " "
				<< ecefcoords.y << ecefcoords.z;
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}

}

void trajectoryContainer::write_to_cout_test(SatID query_sat,CivilTime query_time)
{
	gps_eph_map::const_iterator it;
	std::map<CivilTime, mTrajectoryData>::const_iterator kt;
	mTrajectoryData outputData;

	CivilTime time;
	GPSWeekSecond gpswns;
	ECEFCoordinate ecefcoords;

	it = trajectoryDataContainer.begin();
	std::advance(it, 8);
	sat = (*it).first;
	//std::map<CivilTime, mTrajectoryData> output = trajectoryDataContainer.at(sat);
	std::map<CivilTime, mTrajectoryData> output = trajectoryDataContainer.at(query_sat);

	kt = output.begin();
	std::advance(kt, 10);
	time = (*kt).first;

	//outputData = (*kt).second;
	outputData = output.at(query_time);
	std::cout << sat << "     TIME: " << time << " pRange: " << outputData.pseudorange 
		<< "  positions: " << outputData.xvt.x << std::endl;
}

SatID trajectoryContainer::getSatIDObject(int i, SatID::SatelliteSystem sys = SatID::SatelliteSystem::systemGPS)
{
	//SV's are ordered
	gps_eph_map::const_iterator it = trajectoryDataContainer.begin();
	if (i > 1) {
		std::advance(it, i - 1);
	}
	SatID querysat;
	
	std::cout << (*it).first << "   "  ;
	if ((*it).first.system != sys)
		return (*it).first;			//TODO: return invalid SatID
	return (*it).first;
}

CivilTime trajectoryContainer::getCivilTimeObject(int yr, int mo, int da, int hr, int min, int sec)
{
	CivilTime returnTime;
	returnTime.setTimeSystem(TimeSystem::GPS);
	returnTime.year = yr;
	returnTime.month = mo;
	returnTime.day = da;
	returnTime.hour = hr;
	returnTime.minute = min;
	returnTime.second = sec;

	std::cout << returnTime << "  ";
	return returnTime;
}
