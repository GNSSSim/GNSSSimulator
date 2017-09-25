// Simulator.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Simulator.h"



using namespace gpstk;
using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	/////-------------- PRE TEST OF INCLUDES--------------------\\\\\\\\\\\\
	GPSTime gpstime;
	gpstk::Position pos;
	FULLFrame frame;
	cout << "Position is: " << pos << endl;
	pos.setECEF(-1575232.0141, -4707872.2332, 3993198.4383);
	cout << "Position is: " << pos << endl;
	cout << "ECEF transformed to LLH(Geodetic): " << pos.transformTo(gpstk::Position::Geodetic) << endl;
	std::cout << "LeapSeconds of 1993.09.21. is: " << gpstk::TimeSystem::getLeapSeconds(1993, 9, 21) << std::endl;
	cout << "Pre-Debug tests ended" << endl << "---------------------------------" << endl;
	/////-------------- END OF PRE DEBUG TEST--------------------\\\\\\\\\\\\
	
	int ProcessFiles();
	clock_t totaltime(clock());
	Epoch wallclkbeg;
	wallclkbeg.setLocalTime();


	ProcessFiles();
	return 0;
}

int ProcessFiles(void) throw(Exception) 
{
	try {


		int iret;
		int indexC1;
		Rinex3ObsStream istrm;
		Rinex3ObsHeader Rhead, Rheadout;
		Rinex3ObsData Rdata;
		RinexDatum dataobj;

		Rinex3NavStream inavstrm;
		Rinex3NavHeader Rnavhead;
		Rinex3NavData Rnavdata;

		GPSEphemerisStore bceStore;
		Xvt xvt_data;

		string filepath_obs("..\\SimulatorTest\\TestFiles\\RINEX_obs\\mobs2530.17o");
		string filepath_nav("..\\SimulatorTest\\TestFiles\\RINEX_nav\\mobs2530.17n");

		RinexSatID sat;
		RinexSatID tsat(-1, SatID::systemGPS);

		iret = 0;

		//Open the files
		istrm.open(filepath_obs, ios::in);
		inavstrm.open(filepath_nav.c_str(), ios::in);

		if (!istrm.is_open() || !inavstrm.is_open()) {
			LOG(WARNING) << "Warning : could not open file ";
			iret = 1;
		}
		try
		{
			istrm >> Rhead;
			inavstrm >> Rnavhead;

			Rhead.dump(cout);
			Rnavhead.dump(cout);
			try
			{
				indexC1 = Rhead.getObsIndex("C1");
			}
			catch (...)
			{
				exit(1);
			}
			

			map<string, vector<RinexObsID>>::const_iterator kt;
			for (kt = Rhead.mapObsTypes.begin();kt != Rhead.mapObsTypes.end();kt++) {
				sat.fromString(kt->first);
				sat.dump(cout);
				cout << "  " << sat.systemChar() << endl;
			}

			// Store Ephemeris Data
			while (inavstrm >> Rnavdata) bceStore.addEphemeris(Rnavdata);

			while (istrm >> Rdata) {
				//Rdata.dump(cout);
				vector<SatID> prnVec;			// According to Ex4
				vector<double> rangeVec;
				CivilTime civtime(Rdata.time);
				Rinex3ObsData::DataMap::const_iterator it;


				// Iterate over observations
				for (it = Rdata.obs.begin();it != Rdata.obs.end();it++) {
					double C1(0.0);
					try
					{
						sat = (*it).first; //Get Sat ID
					    //		Skip if Sat is not GPS		Skip if Observations are less than 7
						if (SatID::systemGPS != sat.system || (*it).second.capacity() != 7) continue;
						C1 = Rdata.getObs((*it).first, indexC1).data;	//Get C1 Pseudorange observation

						xvt_data = bceStore.getXvt((*it).first, civtime);

						cout << civtime << " " << sat << " " << C1 << " XVT: " << xvt_data << endl;
						
					}
					catch (...)
					{
						cout << "C1 not found" << endl;
					}
				}
				
				
			}
		}
		catch (const std::exception& e)
		{

		}





		return 0;
	}
	catch (...) {

		return 1;
	}
}


