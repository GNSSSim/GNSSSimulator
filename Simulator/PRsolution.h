#pragma once

#include "TrajectoryStore.hpp"
#include "satDataContainer.h"
#include <math.h>

class PRsolution {

public:

	/* Get the calculated "Pseudorange" without any additional errors applied.
		@param: Trajectory position
		@param: Satellite position
		@return: double pseudorange
	*/
	double getPRSolution_abs(gpstk::Position&,gpstk::Position&);

private:



	gpstk::Position trajPos, satPos;

};