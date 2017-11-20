#pragma once


#include "trajectoryReader.h"
#include "TrajectoryData.hpp"
#include "TrajectoryStore.hpp"

//#include "Rinex3NavBase.hpp"
#include "Rinex3NavHeader.hpp"
#include "Rinex3NavData.hpp"
//#include "Rinex3NavStream.hpp"

#include "GPSEphemerisStore.hpp"
//#include "GPSEphemeris.hpp"


#include "Position.hpp"
#include "Xvt.hpp"

#include "PRSolution2.hpp"

using namespace gnsssimulator;
using namespace gpstk;

class PseudoRangeCalculator
{
public:
	PseudoRangeCalculator();
	~PseudoRangeCalculator();

	void ProcessTrajectoryFile(const char*);
	void ProcessEphemerisFile(const char*);
	bool isSatVisible(const Position, const CommonTime, const SatID, double&);
	bool calcPseudoRange(const CommonTime, const SatID, double&);
	bool calcPseudoRangeTrop(const CommonTime, const SatID, double&, TropModel* tropptr);
	

	double elevationLimitinDegree = 10;
	bool isTrajectoryRead = false;
	bool isEphemerisRead = false;
	TrajectoryStore trajStore;
	GPSEphemerisStore bceStore;

	/*Calculate  TropModel Delays from outside of the class
	@Inputs : Position Reciever Position
			  CommonTime time
			  vector<SatID> containing the satellites
			  TropModel* pointer for the Model to use
	@output delays: the vector of time delays for each satellite
	*/
	void CalculateTropModelDelays(const Position recPos,const CommonTime time,const vector<SatID> satVec,TropModel* tropmdl,vector<double>& delays);
	double CalculateTropModelDelays(const Position recPos, const CommonTime time, const Xvt satPos, TropModel* tropmdl);

private:
	const double C_MPS = 2.99792458e8;
	double calcPseudoRangeNaive(const TrajectoryData, const Xvt);
	bool isSatVisible(const Position, const CommonTime, const SatID, double&, Xvt&);
	Xvt getSatXvt(const Position, const CommonTime, const SatID);
	void earthRotationCorrection(const double, Xvt*);
};

