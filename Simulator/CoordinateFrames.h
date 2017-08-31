#pragma once

typedef struct LLHCoordinate_s{
	double latidute;
	double longitude;
	double height;
}LLHCoordinate;

typedef struct ECEFCoordinate_s{
	double x;
	double y;
	double z;
}ECEFCoordinate;