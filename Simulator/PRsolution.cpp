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

