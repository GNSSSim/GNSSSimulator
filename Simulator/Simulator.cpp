// Simulator.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Simulator.h"
#include "Navigation_examples.h"
#include "Test_Trajectory_Class.hpp"

using namespace gpstk;
using namespace std;


satDataContainer satDataContainer_c;
GPSEphemerisStore bceStore;

int _tmain(int argc, _TCHAR* argv[])
{
	/// Function Declarations
	int ProcessFiles();

	/// End of Declarations
	//Navigation_examples_1();

	//Test_Trajectory_1();
	//Test_Trajectory_2();
	//Test_Trajectory_3();
	//Test_Trajectory_4();
	//Test_Trajectory_5();
	//Test_Trajectory_6();
	//Test_Trajectory_7();
	//Test_Trajectory_8();
	//Test_Trajectory_9();
	//Test_Trajectory_10();
	//Test_Trajectory_11();
	Test_Trajectory_12();

	/*
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
	
	/// Read in RINEX files
	ProcessFiles();
	

	satDataContainer_c.write_to_cout_test(satDataContainer_c.getSatIDObject(4, SatID::systemGPS), satDataContainer_c.getCivilTimeObject(2017, 9, 10, 1, 13, 30));
	GPSEphemeris orbiteph_test = bceStore.findEphemeris(satDataContainer_c.getSatIDObject(4, SatID::systemGPS), satDataContainer_c.getCivilTimeObject(2017, 9, 10, 1, 13, 35));
	cout << endl << "Offsetepoch: " << orbiteph_test.svXvt(satDataContainer_c.getCivilTimeObject(2017, 9, 10, 1, 13, 35));
	cout << endl << endl << std::setprecision(10) << orbiteph_test.svXvt(satDataContainer_c.getCivilTimeObject(2017, 9, 10, 1, 14, 0)).x;
	satDataContainer_c.write_to_cout_test(satDataContainer_c.getSatIDObject(4, SatID::systemGPS), satDataContainer_c.getCivilTimeObject(2017, 9, 10, 1, 14, 0));
	// TODO: ^^^^ DELETE THESE ^^^^

	cout << endl << endl << "------------" << endl;
	OrbitEph query_ephemeris;
	CivilTime query_time = satDataContainer_c.getCivilTimeObject(2017, 9, 10, 1, 13, 30.0001);
	try
	{
		query_ephemeris = satDataContainer_c.getSatInfoAtEpoch(satDataContainer_c.getSatIDObject(4, SatID::systemGPS), query_time);
		cout << query_ephemeris.svXvt(query_time) << endl;
	}
	catch (const std::exception& e)
	{
		cout << endl << e.what();
	}
	*/

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
		
		Xvt xvt_data;

		string filepath_obs("..\\SimulatorTest\\TestFiles\\RINEX_obs\\mobs2530.17o");
		string filepath_nav("..\\SimulatorTest\\TestFiles\\RINEX_nav\\mobs2530.17n");

		RinexSatID sat;

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
			cout << "Parsing Started. Wait for [ERROR] or a [FLAG:...] message." << endl;
			istrm >> Rhead;
			inavstrm >> Rnavhead;

			try
			{
				indexC1 = Rhead.getObsIndex("C1");	//Pseudorange obs index
			}
			catch (...)
			{
				exit(1);
			}

			// Store Ephemeris Data
			while (inavstrm >> Rnavdata) {
				bceStore.addEphemeris(Rnavdata);			//TODO: Delete this EphemerisStore when trajectoryContainer is implemented for storage.
			}

			while (istrm >> Rdata) {
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
						C1 = Rdata.getObs((*it).first, indexC1).data;			//Get C1 Pseudorange observation
						xvt_data = bceStore.getXvt((*it).first, civtime);		//Get XVT data

						satDataContainer_c.assembleTrajectories(sat, civtime, xvt_data,C1);	//Pass data to storage interface
						satDataContainer_c.assemblePseudoRangeContainer(sat, civtime, C1);
						//cout << civtime << " " << sat << " " << C1 << " XVT: " << xvt_data << endl;	// TODO: delete later (debug cout)
						
					}
					catch (...)
					{
						cout << "WARNING: C1 not found for SV:   " << sat << " at epoch:   " << civtime << endl;
					}
				}
			}
			//Add EphemerisStore to Container class
			satDataContainer_c.passEphemerisStore(bceStore);
			cout << "[FLAG: Success] Finished Rinex parsing." << endl;
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


