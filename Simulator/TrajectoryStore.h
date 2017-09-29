#pragma once

#include <iostream>
#include <map>
#include "TrajectoryData.hpp"

namespace gnsssimulator {
	class TrajectoryStore
	{
	public:
		TrajectoryStore();
		~TrajectoryStore();

		void TrajectoryStore::addPosition(gpstk::GPSWeekSecond&, TrajectoryData&);


	protected:
		typedef std::map<gpstk::GPSWeekSecond, TrajectoryData> TrajectoryMap;
		TrajectoryMap TrajStore;
	};

}