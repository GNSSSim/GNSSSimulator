#include "stdafx.h"
#include "TrajectoryData.hpp"

namespace gnsssimulator 
{
	using namespace gpstk::StringUtils;
	using namespace std;

	void TrajectoryData::reallyPutRecord(gpstk::FFStream& s) const
		throw(std::exception, gpstk::FFStreamError,
			gpstk::StringUtils::StringException) {
	
		return;
	}

	/**
	* This function retrieves a RINEX NAV record from the given FFStream.
	* If an error is encountered in reading from the stream, the stream
	* is returned to its original position and its fail-bit is set.
	* @throws StringException when a StringUtils function fails
	* @throws FFStreamError when exceptions(failbit) is set and
	*  a read or formatting error occurs.  This also resets the
	*  stream to its pre-read position.
	*/
	void TrajectoryData::reallyGetRecord(gpstk::FFStream& ffs)
		throw(std::exception, gpstk::FFStreamError,
			gpstk::StringUtils::StringException) {

		TrajectoryStream& strm = dynamic_cast<TrajectoryStream&>(ffs);

		if (!strm.headerRead)
			strm >> strm.header;

		if (coorSys == gpstk::Position::CoordinateSystem::Unknown) {
			this->coorSys = strm.header.coorSys;
		}

		string line;

		strm.formattedGetLine(line, true);

		getTime(line);
		getPosition(line);

		return;
	}

	void TrajectoryData::getTime(const std::string& currentLine)
		throw(gpstk::StringUtils::StringException, gpstk::FFStreamError)
	{
		try
		{
			gpsTime.week = asInt(currentLine.substr(0, 4));
			gpsTime.sow = asDouble(currentLine.substr(7, 7));
		
		}
		catch (std::exception &e)
		{
			gpstk::FFStreamError err("std::exception: " +
				string(e.what()));
			GPSTK_THROW(err);
		}
	}

	void TrajectoryData::getPosition(const std::string& currentLine)
		throw(gpstk::StringUtils::StringException, gpstk::FFStreamError)
	{
		try
		{
			double coor1 = asDouble(currentLine.substr(15, 13));
			double coor2 = asDouble(currentLine.substr(28, 13));
			double coor3 = asDouble(currentLine.substr(41, 13));

			pos = gpstk::Position(	const_cast<const double&>(coor1), 
									const_cast<const double&>(coor2), 
									const_cast<const double&>(coor3),
									
									coorSys);
			cout << gpsTime << endl; 
			cout << pos << endl;
		}
		catch (std::exception &e)
		{
			gpstk::FFStreamError err("std::exception: " +
				string(e.what()));
			GPSTK_THROW(err);
		}
	}

}