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

		gpstk::Position::CoordinateSystem coorSys = gpstk::Position::CoordinateSystem::Unknown;

		TrajectoryData& addPosition(TrajectoryData);
		TrajectoryData& findPosition(gpstk::GPSWeekSecond);

		bool TrajectoryStore::operator==(const TrajectoryStore& other) const;
		bool TrajectoryStore::operator!=(const TrajectoryStore& other) const;

	protected:
		bool isCoorSystemSet = false;
		typedef std::map<gpstk::GPSWeekSecond, TrajectoryData> TrajectoryMap;
		TrajectoryMap TrajStore;
		void setCorrdinateSystem(gpstk::Position::CoordinateSystem);
		bool compare(const TrajectoryStore& other) const;
	};

}