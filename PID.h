#pragma once
#ifndef    PID_H
#define    PID_H

#include <iostream>


class PID
{
public:


	PID(double Kp, double Ki = 0, double Kd = 0);
	void setSaturation(double min, double max);
	double getCommand(double desiredValue, double dt);

private:

	double t_Kp, t_Ki, t_Kd, t_min, t_max, t_integral, t_lastError;

};
#endif
