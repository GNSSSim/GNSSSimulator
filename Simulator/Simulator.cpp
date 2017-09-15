// Simulator.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Simulator.h"

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{

	int myprn;

	cout << "Name PRN (1..32): ";
	cin >> myprn;

	//double gamma = (L1_FREQ_GPS / L2_FREQ_GPS)*(L1_FREQ_GPS / L2_FREQ_GPS);
	cout << "RINEX data file reading Started" << endl;

	gpstk::RinexObsStream rin("..\\SimulatorTest\\TestFiles\\RINEX_obs\\mobs2340.17o");
	gpstk::RinexObsStream rout("..\\SimulatorTest\\TestFiles\\RINEX_obs\\mobs2340.17o.new", ios::out | ios::trunc);

	rin.exceptions(ios::failbit);
	gpstk::RinexObsHeader head;
	gpstk::RinexObsData data;
	gpstk::RinexDatum dataobj;

	//Read the RINEX header
	rin >> head;
	head.dump(cout);

	rout << rout.header;

	/*
	while (rin >> data) {
		rout << data;
		//cout << data;
	}
	*/


	cout << "Main Process Finished!" << endl;
	getchar();
	cin >> myprn;

	return 0;
}


