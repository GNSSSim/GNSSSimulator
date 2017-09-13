// Simulator.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Simulator.h"

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	double llh[3] = { 0.75, 0.75, 100 };
	double ecef[3] = {0,0,0};
	GPSTime gpstime;

	gpstk::Position pos;
	FULLFrame frame;
	cout << "Position is: " << pos << endl;
	pos.setECEF(-1575232.0141, -4707872.2332, 3993198.4383);
	cout << "Position is: " << pos << endl;
	cout << "ECEF transformed to LLH(Geodetic): " << pos.transformTo(gpstk::Position::Geodetic) << endl;


	std::cout << "LeapSeconds of 1993.09.21. is: " << gpstk::TimeSystem::getLeapSeconds(1993, 9, 21) << std::endl;
	cout << "Pre-Debug tests ended" << endl << "---------------------------------" << endl;

	char* path = "..\\SimulatorTest\\TestFiles\\TrajectoryTestFiles\\goodTrajectoryFilewECEF.txt";
	trajectoryReader trajectoryReader(path);
	frame = trajectoryReader.readLine_as_frame();
	cout << frame.GPSTime.WN << " " << frame.GPSTime.ToW << " " << frame.ECEFcoordinates.x << " " << frame.ECEFcoordinates.y << " " << frame.ECEFcoordinates.z << " " << frame.LLHcoordinates.latitude << " " << frame.LLHcoordinates.longitude << " " << frame.LLHcoordinates.height << endl;
	frame = trajectoryReader.readLine_as_frame();
	cout << frame.GPSTime.WN << " " << frame.GPSTime.ToW << " " << frame.ECEFcoordinates.x << " " << frame.ECEFcoordinates.y << " " << frame.ECEFcoordinates.z << " " << frame.LLHcoordinates.latitude << " " << frame.LLHcoordinates.longitude << " " << frame.LLHcoordinates.height << endl;
	frame = trajectoryReader.readLine_as_frame();
	cout << frame.GPSTime.WN << " " << frame.GPSTime.ToW << " " << frame.ECEFcoordinates.x << " " << frame.ECEFcoordinates.y << " " << frame.ECEFcoordinates.z << " " << frame.LLHcoordinates.latitude << " " << frame.LLHcoordinates.longitude << " " << frame.LLHcoordinates.height << endl;
	frame = trajectoryReader.readLine_as_frame();
	cout << frame.GPSTime.WN << " " << frame.GPSTime.ToW << " " << frame.ECEFcoordinates.x << " " << frame.ECEFcoordinates.y << " " << frame.ECEFcoordinates.z << " " << frame.LLHcoordinates.latitude << " " << frame.LLHcoordinates.longitude << " " << frame.LLHcoordinates.height << endl;

	getchar();

	return 0;
}


