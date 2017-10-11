#pragma once

#include "TrajectoryStore.hpp"
#include "satDataContainer.h"

#include "Rinex3ObsStream.hpp"
#include "Rinex3ObsHeader.hpp"

#include <math.h>

namespace gnsssimulator {


class PRsolution {

public:

	/* Get the calculated "Pseudorange" without any additional errors applied.
		@param: Trajectory position
		@param: Satellite position
		@return: double pseudorange
	*/
	double getPRSolution_abs(gpstk::Triple&,gpstk::Triple&);

	/*	Write calculated C1 solution to a valid Rinex file
		/Uses a template input Rinex observation header, which's
		values are changed. Some fields may be invalid.
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