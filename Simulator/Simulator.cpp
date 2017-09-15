// Simulator.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Simulator.h"

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	cout << "RINEX data file reading Started" << endl;

	gpstk::RinexObsStream rin("..\\SimulatorTest\\TestFiles\\RINEX_obs\\mobs2340.17o");
	gpstk::RinexObsStream rout("..\\SimulatorTest\\TestFiles\\RINEX_obs\\mobs2340.17o.new", ios::out | ios::trunc);

	gpstk::RinexObsHeader head;
	rin >> head;
	rout.header = rin.header;
	rout << rout.header;

	gpstk::RinexObsData data;
	while (rin >> data) {
		rout << data;
		//cout << data;
	}
	cout << "ROUT Write finished." << endl;
	getchar();

	return 0;
}


