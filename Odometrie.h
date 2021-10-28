#pragma once
#ifndef    ODOMETRIE_H
#define    ODOMETRIE_H
#define _USE_MATH_DEFINES

#include "wifibotClient.h"
#include <iostream>
#include <cmath>


class Odometrie
{
public:

	const float rayonRoue = 14.3;
	const float distanceRoue = 15.0;

	Odometrie(WifibotClient &robot);
	void Update();
	void PrintData();

private:

	WifibotClient t_robot;
	long t_odoLeft;
	long t_odoRight;
	double x, y, yaw;
	SensorData t_sensors_data;

};
#endif
