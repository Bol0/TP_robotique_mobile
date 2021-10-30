#include "PID.h"



PID::PID(double Kp, double Ki, double Kd) {
	t_Kp = Kp;
	t_Ki = Ki;
	t_Kd = Kd;
	t_min = 0;
	t_max = 0;
	t_integral = 0;
	t_lastError = 0;
}


void PID::setSaturation(double min, double max) {
	t_min = min;
	t_max = max;
}


double PID::getCommand(double erreur, double dt) {

	//proportional
	double command = t_Kp * erreur; 

	//integral
	t_integral += erreur * dt;
	//implémenter une anti-windUp pour l'integral ?
	command += t_integral * t_Ki;

	//Derivate
	command = ((erreur-t_lastError)/dt)*t_Kd; 
	t_lastError = erreur;

	//saturations
	if (t_min != 0 && command < t_min) {
		command = t_min;
	}
	if (t_max != 0 && command > t_max) {
		command = t_max;
	}


	return command;
}