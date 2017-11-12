#include "stdafx.h"
#include "PseudoRangeCalculator.h"


PseudoRangeCalculator::PseudoRangeCalculator()
{
}

PseudoRangeCalculator::~PseudoRangeCalculator()
{
}

void PseudoRangeCalculator::ProcessTrajectoryFile(const char* fileNamewPath) {

	TrajectoryStream trajFileIn(fileNamewPath); //("..\\Simulator\\TrajectoryTestFiles\\TrajectoryFileExample_RinexMatch_rinexcoord_only1.txt");
	TrajectoryHeader trajHeader;
	TrajectoryData trajData;

	isTrajectoryRead = false;
	trajFileIn >> trajHeader;

	while (trajFileIn >> trajData) {
		try { 
			trajStore.addPosition(trajData); 
		} 
		catch(...){
			cout << "Reading Trajectory data was not successfull "<< endl;
		}
	}
	cout << "[FLAG: Success] Trajectory file parsing finished." << endl;
	
	isTrajectoryRead = true;
}

void PseudoRangeCalculator::ProcessEphemerisFile(const char* fileNamewPath) {

	Rinex3NavStream inavstrm;
	Rinex3NavHeader Rnavhead;
	Rinex3NavData Rnavdata;

	isEphemerisRead = false;
	inavstrm.open(fileNamewPath, ios::in);

	if ( !inavstrm.is_open()) {
		cout << "Warning : could not open file ";
		return;
	}

	inavstrm >> Rnavhead;

	while (inavstrm >> Rnavdata) {
		try {
			bceStore.addEphemeris(Rnavdata);
		}
		catch (...) {
			cout << "Error during 'addEphemeris' fnc." << endl;
			//Rnavdata.dump(cout);
		}
	}

	isEphemerisRead = true;
}

bool PseudoRangeCalculator::isSatVisible(const CommonTime time, const SatID satId, double& elevation) {
	Xvt xvt_data;
	return isSatVisible(time, satId, elevation, xvt_data);
}

bool PseudoRangeCalculator::isSatVisible(const CommonTime time, const SatID satId, double& elevation, Xvt& xvt_data) {
	if (isEphemerisRead == false || isTrajectoryRead == false) {
		cout << "Ephemeris or Trajectory file is not processed. " << endl;
		return false;
	}

	if (bceStore.isPresent(satId) == false) {
		return false;
	}
	GPSWeekSecond gpsweeksecs(time);
	TrajectoryData trajData = trajStore.findPosition(gpsweeksecs);
	if (&trajData == NULL) {
		return false;
	}

	WGS84Ellipsoid wgs84ellmodel;

	xvt_data = bceStore.getXvt(satId, time);
	Position SatPos(xvt_data), SitePos(trajData.pos);
	/*SatPos.setEllipsoidModel(&wgs84ellmodel);
	SitePos.setEllipsoidModel(&wgs84ellmodel);
	SitePos.setReferenceFrame(wgs84ellmodel);*/
	elevation = SitePos.elevation(SatPos);

	if (elevation < this->elevationLimitinDegree) {
		return false;
	}
	return true;
}

Xvt PseudoRangeCalculator::getSatXvt(const CommonTime time, const SatID satId) {
	Xvt retXvt;
	double elevation;
	if (bceStore.isPresent(satId) == false) {
		throw;
	}
	try {
		this->isSatVisible(time, satId, elevation, retXvt);
		if (elevation < this->elevationLimitinDegree) {
			throw -1;
		}
	}
	catch (...) {
		throw -1;
	}
	return retXvt;

}

bool PseudoRangeCalculator::calcPseudoRange(const CommonTime Tr, const SatID satId, double& psdrange) {
	Xvt PVT;
	CommonTime tx;
	tx = Tr;

	GPSWeekSecond gpsweeksecs(Tr);
	TrajectoryData trajData = trajStore.findPosition(gpsweeksecs);
	if (&trajData == NULL) {
		return false;
	}

	try {
		PVT = this->getSatXvt(Tr, satId);
	}
	catch (...) {
		psdrange = -1;
		return false;
	}

	psdrange = this->calcPseudoRangeNaive(trajData, PVT);
	if(psdrange<0)
		return false;

	tx += psdrange/this->C_MPS;
	
	PVT = this->getSatXvt(tx, satId);
	tx += PVT.clkbias + PVT.relcorr;

	PVT = this->getSatXvt(tx, satId);

	psdrange = psdrange - C_MPS * (PVT.clkbias + PVT.relcorr);

	return true;
}

double PseudoRangeCalculator::calcPseudoRangeNaive(const TrajectoryData trajData, const Xvt PVT) {

	double psdrange;
	Xvt satXvt;

	Triple triple;
	WGS84Ellipsoid wgs84ellmodel;

	Position satPos(PVT.x);
	satPos.setEllipsoidModel(&wgs84ellmodel);


	Position  roverPos = trajData.pos;
	roverPos.setEllipsoidModel(&wgs84ellmodel);
	Position diff = satPos - roverPos;

	diff.setEllipsoidModel(&wgs84ellmodel);
	psdrange = sqrt(pow(diff.getX(), 2) + pow(diff.getY(), 2) + pow(diff.getZ(), 2));


	return psdrange;
}