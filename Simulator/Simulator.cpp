// Simulator.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Simulator.h"



using namespace gpstk;
using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{

	GPSTime gpstime;

	gpstk::Position pos;
	FULLFrame frame;
	cout << "Position is: " << pos << endl;
	pos.setECEF(-1575232.0141, -4707872.2332, 3993198.4383);
	cout << "Position is: " << pos << endl;
	cout << "ECEF transformed to LLH(Geodetic): " << pos.transformTo(gpstk::Position::Geodetic) << endl;


	std::cout << "LeapSeconds of 1993.09.21. is: " << gpstk::TimeSystem::getLeapSeconds(1993, 9, 21) << std::endl;
	cout << "Pre-Debug tests ended" << endl << "---------------------------------" << endl;

	
	

	return 0;
}


