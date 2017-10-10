#pragma once

#include "TrajectoryStore.hpp"
#include "satDataContainer.h"

#include "Rinex3ObsStream.hpp"

#include <math.h>

namespace gnsssimulator {


class PRsolution {

public:

	/* Get the calculated "Pseudorange" without any additional errors applied.
		@param: Trajectory position
		@param: Satellite position
		@return: double pseudorange
	*/
	double getPRSolution_abs(gpstk::Position&,gpstk::Position&);

	/*	Write calculated solution to a valid Rinex file
	*/
	void createRinexFile(void);

	/* Get Direct Pseudorange from emission time, clock offset and observations
	*/
	double getPR_direct();

	/*Get Pseudorange with iterative method*/
	double getPR_iterative();

private:



	gpstk::Position trajPos, satPos;

	double pr_it_treshold;

};
}