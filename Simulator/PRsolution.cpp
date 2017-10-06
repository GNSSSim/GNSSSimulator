#include "stdafx.h"
#include "PRsolution.h"

double gnsssimulator::PRsolution::getPRSolution_abs(gpstk::Position& in_trajpos, gpstk::Position& in_satpos)
{
	double return_pr;
	gpstk::Position pos_diff = in_trajpos - in_satpos;
	double xdiff = pos_diff.X();
	double ydiff = pos_diff.Y();
	double zdiff = pos_diff.Z();

	return_pr = std::sqrt(std::pow(xdiff,2)+std::pow(ydiff,2)+std::pow(zdiff,2));

	return return_pr;
}

void gnsssimulator::PRsolution::createRinexFile(void)
{
	gpstk::Rinex3ObsHeader out_head;
	gpstk::Rinex3ObsData out_data;
	gpstk::Rinex3ObsStream out_stream("..\\Simulator\\TrajectoryTestFiles\\TrajectoryFileExample_RinexMatch_generatedRINEX.txt",std::ios::out);
	///Test for valid header input -- Prints out succesfully
	/*gpstk::Rinex3ObsStream in_test_stream("..\\SimulatorTest\\TestFiles\\RINEX_obs\\mobs2530.17o", std::ios::in);
	in_test_stream >> out_head;
	out_stream << out_head;*/
	/// Valid header input test END
	out_head.validEoH = 1;
	out_head.clear();
	out_head.agency = "Test";
	out_head.date = "2017.10.06 9:32";
	out_head.valid = 1;
	out_head.fileSys = gpstk::RinexSatID::systemGPS;
	out_head.fileProgram = "program";
	out_head.markerName = "Markername";
	out_head.observer = "Observer";
	out_head.recType = "Rectype";
	out_head.antennaPosition = gpstk::Triple(1.0, 1.0, 1.0);
	out_head.antennaDeltaHEN = gpstk::Triple(2.0, 2.0, 2.0);
	out_head.validMarkerName;
	

	out_stream << out_head;
	out_head.dump(std::cout);

	out_stream.close();
}
