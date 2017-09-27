#include "stdafx.h"
#include "trajectoryContainer.h"

trajectoryContainer::trajectoryContainer()
{
}

trajectoryContainer::~trajectoryContainer()
{
}

void trajectoryContainer::addObsData()
{
}

void trajectoryContainer::addNavData(const GPSEphemeris& gpseph)
{
	ephemerisStore.addEphemeris(gpseph);
}

void trajectoryContainer::assembleTrajectories(SatID sat,CivilTime civtime, Xvt xvt_i)
{
	trajectoryData.xvt = xvt_i;
	trajectoryDataContainer[sat][civtime] = trajectoryData;

}

gps_eph_map trajectoryContainer::getNavData()
{	
	return trajectoryDataContainer;
}
