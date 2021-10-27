#define _USE_MATH_DEFINES
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <chrono>
#include <ctime> 
#include <cmath>

#include "WifibotClient.h"

#define IP_ADRESSE "10.3.141.1"
#define PORT	15020

int SharpLUT[] = { 150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,103,102,101,100,99,
		  96,95,90,88,87,86,85,84,83,82,81,80,79,77,75,74,73,72,71,70,69,68,67,66,65,65,64,64,63,62,61,61,60,60,59,59,58,58,57,57,56,56,56,55,55,55,54,54,54,53,
		  53,53,52,52,51,51,50,50,49,49,49,48,48,47,47,46,46,46,45,45,44,44,43,43,42,42,41,41,41,40,40,40,39,39,39,39,39,38,38,
				  38,38,37,37,37,37,36,36,36,36,35,35,35,35,34,34,34,34,34,34,33,33,33,33,32,32,32,32,32,31,31,31,31,30,30,30,30,30,30,30,
		  30,29,29,29,29,29,29,29,28,28,28,28,28,28,27,27,27,27,27,27,27,26,26,26,26,25,25,25,25,25,25,24,24,24,24,24,23,23,23,
		  23,23,23,22,22,22,22,22,21,21,21,21,21,21,20,20,20,20,19,19,19,19,19,19,18,18,18,18,18,18,17,17,17,16,16,15,15 };

void setSpeed(int left, int right, WifibotClient& robot) {
	unsigned char flags = 1 + 32 + 128;
	if (left > 0) {
		flags += 64;
	}
	if (right > 0) {
		flags += 16;
	}
	robot.SendCommand(abs(left), abs(right),flags);
}

double get_dt(std::chrono::system_clock::time_point &lastTime) {
	std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = now-lastTime;
	lastTime = now;
	return elapsed_seconds.count();
}

void getVitesse(SensorData sensors_data, double &vit_left, double &vit_right) {
	vit_left = (((double)sensors_data.SpeedFrontLeft / 2048) * 2 * M_PI) * 14.5;//convertis la vitesse en cm/s
	vit_right = (((double)sensors_data.SpeedFrontRight / 2048) * 2 * M_PI) * 14.5;
}


void getDistance(SensorData sensors_data, double dt, double &dist_left, double &dist_right){
	double left;
	double right;
	getVitesse(sensors_data, left, right);
	dist_left += left*dt;
	dist_right += right*dt;
}

void majOdometrie(double &x, double &y, double &yaw, double dist_l, double dist_r) {
	if (!(dist_l == 0 && dist_r == 0)) {
		double dist = (dist_l + dist_r) / 2;
		double rayon = 15.0 * (dist_r + dist_l) / (dist_r - dist_l);
		double diff_yaw = dist / rayon;

		//std::cout << "dist : " << dist << "\t rayon : " << rayon << "\t yaw : " << diff_yaw << "\n";

		//coordonees du centre du rayon de courbure
		double x0 = x - rayon * cos(yaw - (M_PI / 2));
		double y0 = y - rayon * sin(yaw - (M_PI / 2));

		//std::cout << "x0 : " << x0 << "\t y0 : " << y0 << "\t thet : "<< diff_yaw<<"\n";

		//on maj les donnees
		if (diff_yaw != 0) { // on verifie qu'on est pas a l'infinie
			if (abs(rayon) == 0) {
				//pas de deplacement sur x et y, juste une rotation pure
				yaw += (dist_l / 15.0);
			}
			else {
				yaw += diff_yaw;
				x = x0 + rayon * cos(yaw - (M_PI / 2));
				y = y0 + rayon * sin(yaw - (M_PI / 2));
			}
		}
		else {
			x += dist * cos(yaw);
			y += dist * sin(yaw);
			if (dist_l == -dist_r) { //rotation pure
				yaw += (dist_r / 15.0);
			}
		}


	}
}



int main(void)
{

	WifibotClient robot;

	/*.........................*/
	/* Connection to the robot */
	/*.........................*/
	char ip[] = "10.3.141.1";
	bool rep = robot.ConnectToRobot(ip, PORT);
	if (rep)
	{
		printf("Connection failed...\n");
		getchar();
		return -1;
	}
	else
	{
		printf("Connection established...\n");
	}


	/*..............*/
	/* Main program */
	/*..............*/

	//init
	SensorData sensors_data;
	auto lastTime = std::chrono::system_clock::now();
	double pos_x = 0;
	double pos_y = 0;
	double yaw = 0;

	for (int i = 0; i < 100; i++) {
		setSpeed(40, 40*((100-i)/50), robot);
		Sleep(100);

		//maj audo
		robot.GetSensorData(&sensors_data);
		double dt = get_dt(lastTime);
		double dist_l = 0;//faut init les dist a zero sinon on add
		double dist_r = 0;
		getDistance(sensors_data, dt, dist_l, dist_r);
		majOdometrie(pos_x, pos_y, yaw, dist_l, dist_r);
		std::cout << "position x : " << pos_x << "\t y : " << pos_y << "\t yaw : " << yaw << "\n";
	}
	for (int i = 0; i < 100; i++) {
		setSpeed(40, -40, robot);
		Sleep(100);

		//maj audo
		robot.GetSensorData(&sensors_data);
		double dt = get_dt(lastTime);
		double dist_l = 0;//faut init les dist a zero sinon on add
		double dist_r = 0;
		getDistance(sensors_data, dt, dist_l, dist_r);
		majOdometrie(pos_x, pos_y, yaw, dist_l, dist_r);
		std::cout << "position x : " << pos_x << "\t y : " << pos_y << "\t yaw : " << yaw << "\n";
	}
	setSpeed(0, 0, robot);
	return 0;
}

