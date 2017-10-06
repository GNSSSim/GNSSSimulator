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



private:



	gpstk::Position trajPos, satPos;

};
}