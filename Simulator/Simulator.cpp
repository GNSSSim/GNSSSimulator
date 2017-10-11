// Simulator.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Simulator.h"
#include "Navigation_examples.h"
#include "Test_Trajectory_Class.hpp"
#include "Test_simulatePseudoRange.hpp"

using namespace gpstk;
using namespace std;


satDataContainer satDataContainer_c;		//Stores C1 and Ephemeris Data for the SVs
GPSEphemerisStore bceStore;
gnsssimulator::TrajectoryStore trajStore;
gnsssimulator::PRsolution prsolution;

//typedef map<CivilTime, pair<Triple, map<SatID, Triple>>> PRSolutionContainer;
typedef map<SatID, Triple> SatDataEpoch;
typedef pair<Triple, SatDataEpoch> SolutionDataBlock;

int _tmain(int argc, _TCHAR* argv[])
{

	/// Function Declarations
	int ProcessFiles();
	int ProcessTrajectoryFile();
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
	//Test_Trajectory_12();
	//Test_Trajectory_13();
	//Test_Trajectory_14();
	//Test_Trajectory_15();

	//makeSimplePseudoRange();

	
	
	/// Read in RINEX files
	ProcessFiles();
	/// Read Rover Trajectory file
	ProcessTrajectoryFile();

			//DEBUG FOR RINEX PROCESS
	/*cout << endl << endl << "------------" << endl;
	OrbitEph query_ephemeris;
	CivilTime query_time = satDataContainer_c.getCivilTimeObject(2017, 9, 10, 1, 13, 37.456789);
	SatID query_sat = satDataContainer_c.getSatIDObject(4, SatID::systemGPS);
	try
	{
		query_ephemeris = satDataContainer_c.getSatInfoAtEpoch(query_sat, query_time);
		cout << "EPHQuery: " << query_ephemeris.svXvt(query_time) << endl;
		Xvt xvt_data = satDataContainer_c.getEphemerisStore().getXvt(query_sat, query_time);
		cout << "StoreQuery: " << xvt_data.x << endl;
	}
	catch (const std::exception& e)
	{
		cout << endl << e.what();
	}*/
	

	//DEBUG FOR PRSOLUTION
	vector<GPSWeekSecond>traj_timevec = trajStore.listTime();
	double Prange;
	
	SatDataEpoch satDataEpoch;
	SolutionDataBlock solutionDataBlock;
	gnsssimulator::PRsolution::PRSolutionContainer prsolutionContainer;

	for (auto& it : traj_timevec) {
		CivilTime civtime = it.convertToCommonTime();
		cout << setw(30) << endl;
		cout << "Next Epoch: " << endl;
		cout << it << "  converted to civtime: " << civtime << endl;

		gnsssimulator::TrajectoryData data = trajStore.findPosition(it);
		cout << "Rover Position:     " << data.pos << endl << endl;



		for (auto& satid_it : satDataContainer_c.getSatIDvectorlist()) {
			try
			{
				Xvt xvt_data = satDataContainer_c.getEphemerisStore().getXvt(satid_it, civtime);
				Prange = prsolution.getPRSolution_abs(data.pos, xvt_data.x);				

				satDataEpoch[satid_it] = xvt_data.x;

				cout << " Sat ID: " << satid_it << " Position: "
					<< xvt_data.x << " PseudoRange: " << Prange
					<< endl;
			}
			catch (const gpstk::InvalidRequest& e)
			{
				//cout << "[Warning] Can't get OrbitEph for " << satid_it << " at: " << civtime << endl;
			}
		}
		solutionDataBlock.first = data.pos;
		solutionDataBlock.second = satDataEpoch;
		prsolutionContainer[civtime] = solutionDataBlock;
	}
	cout << "Creating Rinex File. " << endl;
	prsolution.prepareRinexData(prsolutionContainer);
	prsolution.createRinexFile();

	return 0;
}

// TODO: Rename to ProcessRinexFile and refactor code to handle Rinex dynamically.
int ProcessFiles(void) throw(Exception) 
{
	try {
		int iret;
		iret = 0;
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
				bceStore.addEphemeris(Rnavdata);			
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

						//satDataContainer_c.assembleTrajectories(sat, civtime, xvt_data,C1);	//Pass data to storage interface
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

int ProcessTrajectoryFile(void){

	gnsssimulator::TrajectoryStream trajFileIn("..\\Simulator\\TrajectoryTestFiles\\TrajectoryFileExample_RinexMatch.txt");
	gnsssimulator::TrajectoryHeader trajHeader;
	gnsssimulator::TrajectoryData trajData;

	trajFileIn >> trajHeader;
	
	while (trajFileIn >> trajData) {
		trajStore.addPosition(trajData);
	}
	cout << "[FLAG: Success] Trajectory file parsing finished." << endl;
	return 0;
}


