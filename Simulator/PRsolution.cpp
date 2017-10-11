#include "stdafx.h"
#include "PRsolution.h"

double gnsssimulator::PRsolution::getPRSolution_abs(gpstk::Triple& in_trajpos, gpstk::Triple& in_satpos)
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
	gpstk::Rinex3ObsHeader ref_head;
	gpstk::Rinex3ObsData out_data;
	gpstk::Rinex3ObsStream ref_stream_in("..\\SimulatorTest\\TestFiles\\RINEX_obs\\mobs2530.17o");
	gpstk::Rinex3ObsStream out_stream("..\\Simulator\\TrajectoryTestFiles\\generatedRINEX.11o",std::ios::out);
	
	ref_stream_in >> ref_head;

#pragma region Header Manipulation
	ref_head.fileProgram = "GNSS Simulator PR";
	ref_head.agency = "---";

	ref_head.commentList.clear();
	ref_head.commentList.push_back("C1 modelled using GNSSSIM");
	ref_head.commentList.push_back("https://github.com/GNSSSim/GNSSSimulator");
	ref_head.commentList.push_back("Header contents might be invalid. Only C1 is important.");
	ref_head.obsTypeList.clear();

	RinexObsID obsID;
	gpstk::Rinex3ObsHeader::RinexObsVec obsvec;

	obsID.type = ObsID::otRange;
	obsID.band = ObsID::cbL1;
	obsID.code = ObsID::tcCA;
	obsvec.push_back(obsID);
	ref_head.mapObsTypes.clear();
	ref_head.mapObsTypes["G"] = obsvec;

	ref_head.R2ObsTypes.clear();
	ref_head.R2ObsTypes.push_back("C1");
#pragma endregion

#pragma region Data Manipulation
	//aa
	//aa
#pragma endregion
	
	ref_head.dump(cout);
	out_stream << ref_head;

	out_stream.close();
}
