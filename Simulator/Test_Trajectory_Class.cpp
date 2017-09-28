#include "stdafx.h"
#include "TrajectoryHeader.hpp"
#include "TrajectoryData.hpp"
#include "TrajectoryStream.hpp"
#include "RinexNavData.hpp"

#include "Test_Trajectory_Class.hpp"

using namespace gpstk::StringUtils;
using namespace std;

void Test_Trajectory_1(void) {


	gnsssimulator::TrajectoryStream trajFileIn("C:\\Users\\LUS2BP\\Source\\Repos\\GNSSSimulator\\Simulator\\TrajectoryTestFiles\\Test1_TrajectoryFileExample.txt");
	gnsssimulator::TrajectoryStream trajFileOut("C:\\Users\\LUS2BP\\Source\\Repos\\GNSSSimulator\\Simulator\\TrajectoryTestFiles\\Test1_TrajectoryFileExample_Out.txt", std::ios::out);
	gnsssimulator::TrajectoryHeader trajHeader;
	
	trajFileIn >> trajHeader;
	trajFileOut << trajHeader;

	trajFileIn.close();
	trajFileOut.close();
}

void Test_Trajectory_2(void) {


	gnsssimulator::TrajectoryStream trajFileIn("..\\Simulator\\TrajectoryTestFiles\\Test2_TrajectoryFileExample.txt");
	gnsssimulator::TrajectoryStream trajFileOut("..\\Simulator\\TrajectoryTestFiles\\Test2_TrajectoryFileExample_Out.txt", std::ios::out);
	gnsssimulator::TrajectoryHeader trajHeader;
	gnsssimulator::TrajectoryData trajData;

	trajFileIn >> trajHeader;
	trajFileOut << trajHeader;
	
	cout << "Next epoch" << endl;
	while (trajFileIn >> trajData) {
		cout << endl <<"Next epoch" << endl;
	}


	trajFileIn.close();
	trajFileOut.close();


}