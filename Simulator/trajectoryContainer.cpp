#include "stdafx.h"
#include "trajectoryContainer.h"

satDataContainer::satDataContainer()
{
}

satDataContainer::~satDataContainer()
{
}


void satDataContainer::assembleTrajectories(SatID sat,CivilTime civtime, Xvt xvt_i, double pseudorange)
{
	trajectoryData.xvt = xvt_i;
	trajectoryData.pseudorange = pseudorange;
	trajectoryDataContainer[sat][civtime] = trajectoryData;
}

void satDataContainer::assemblePseudoRangeContainer(SatID inSat, CivilTime inTime, double inPRange)
{
	pseudoRangeContainer[inSat][inTime] = inPRange;

}

void satDataContainer::passEphemerisStore(GPSEphemerisStore &eph)
{
	ephemerisStore = eph;
}


bool satDataContainer::isEpochonDarkSide(CivilTime civiliantime, std::vector<CivilTime>& referenceEpoch)
{
	if (civiliantime < referenceEpoch.front() || civiliantime > referenceEpoch.back())
		return true;
	else
		return false;
}

std::vector<CivilTime> satDataContainer::getEpochVectorforSat(SatID& querySat)
{
	std::map<CivilTime,double> queryMap = pseudoRangeContainer.at(querySat);
	std::vector<CivilTime> outVector;

	for (auto& x : queryMap)
		outVector.push_back(x.first);
	
	return outVector;
}

void satDataContainer::write_to_cout_all()
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

void satDataContainer::write_to_cout_test(SatID query_sat,CivilTime query_time)
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

	std::vector<CivilTime> epochs;
	for (auto& x : output)
		epochs.push_back(x.first);

	kt = output.begin();
	std::advance(kt, 10);
	time = (*kt).first;

	//outputData = (*kt).second;
	try
	{
		if (isEpochonDarkSide(query_time, epochs))
			std::cout << std::endl << "[ERROR] EPOCH IS ON DARK SIDE" << std::endl;
		outputData = output.at(query_time);
		std::cout << std::endl << query_sat << "     TIME: " << query_time << " pRange: " << outputData.pseudorange
			<< "  positions: " << std::setprecision(10) << outputData.xvt.x << std::endl;
	}
	catch (const std::exception&)
	{
		std::cout << std::endl << "[ERROR] Epoch for " << query_sat << " not found!" << std::endl;
	}
	
}

SatID satDataContainer::getSatIDObject(int i, SatID::SatelliteSystem sys = SatID::SatelliteSystem::systemGPS)
{
	//SV's are ordered
	gps_eph_map::const_iterator it = trajectoryDataContainer.begin();
	if (i > 1) {
		std::advance(it, i - 1);
	}
	SatID querysat;

	if ((*it).first.system != sys)
		return (*it).first;			//TODO: return invalid SatID
	return (*it).first;
}



CivilTime satDataContainer::getCivilTimeObject(int yr, int mo, int da, int hr, int min, int sec)	//TODO: double sec for subsecundum acquisiton
{
	CivilTime returnTime;
	returnTime.setTimeSystem(TimeSystem::GPS);
	returnTime.year = yr;
	returnTime.month = mo;
	returnTime.day = da;
	returnTime.hour = hr;
	returnTime.minute = min;
	returnTime.second = sec;

	return returnTime;
}

OrbitEph satDataContainer::getSatInfoAtEpoch(SatID query_sat, CivilTime query_time)
{
	GPSEphemeris returnEph;

	returnEph = ephemerisStore.findEphemeris(query_sat, query_time);
	return returnEph;
}
