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

	RinexReader rinexreader;
	
	//rinexreader.readFile("..\\SimulatorTest\\TestFiles\\RINEX_obs\\mobs2340.17o");
	gpstk::Rinex3ObsStream rin("..\\SimulatorTest\\TestFiles\\RINEX_obs\\mobs2340.17o");
	gpstk::Rinex3ObsStream rout("..\\SimulatorTest\\TestFiles\\RINEX_obs\\mobs2340.17o.new", ios::out | ios::trunc);

	rin.exceptions(ios::failbit);
	gpstk::Rinex3ObsHeader head;
	gpstk::Rinex3ObsData data;
	gpstk::RinexDatum dataobj;

	//Read the RINEX header
	rin >> head;
	head.dump(cout);


	//Get Indexes
	//int indexP1 = head.getObsIndex("P1");
	//int indexP2 = head.getObsIndex("P2");
	double gamma = (gpstk::L1_FREQ_GPS / gpstk::L2_FREQ_GPS)*(gpstk::L1_FREQ_GPS / gpstk::L2_FREQ_GPS);


	//Loop through epochs
	while (rin >> data) {
		gpstk::CivilTime civtime(data.time);
		
		gpstk::SatID prn(myprn, gpstk::SatID::systemGPS);
		gpstk::Rinex3ObsData::DataMap::iterator pointer = data.obs.find(prn);
		if (pointer == data.obs.end())
		{
			cout << "PRN " << myprn << " not in view " << endl;
		}
		else
		{
			/*dataobj = data.getObs(prn, indexP1);
			double P1 = dataobj.data;

			dataobj = data.getObs(prn, indexP2);
			double P2 = dataobj.data;
			
			dataobj = data.getObs(prn, "P1", head);
			double P1 = dataobj.data;
			dataobj = data.getObs(prn, "P2", head);
			double P2 = dataobj.data;
			dataobj = data.getObs(prn, "L1", head);
			double L1 = dataobj.data;

			double mu = P1 - L1*(gpstk::C_MPS / P1 -L1*(gpstk::C_MPS/ gpstk::L1_FREQ_GPS) -2*(P1 -P2)/(1-gamma));
			
			cout << "PRN" << myprn << " biased multipath " << mu << endl;
			*/
		}

		cout << rin.recordNumber<<" "<< civtime << " " << prn << endl;
		//data.obs.find(prn);

		//dataobj = data.getRecord(prn);
	}
	cout << rin.recordNumber << " epochs read." << endl;

	cout << "Main Process Finished!" << endl;
	getchar();
	cin >> myprn;

	return 0;
}


