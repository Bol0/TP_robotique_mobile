#define _USE_MATH_DEFINES
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <chrono>
#include <ctime> 
#include <cmath>

#include "WifibotClient.h"
#include "Odometrie.h"

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
	robot.SendCommand(abs(left), abs(right), flags);
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
	Odometrie odo(&robot);

	/*for (int i = 0; i < 100; i++) {
		odo.Update();
		odo.PrintData();
		double erreur = 2*M_PI - odo.getYaw();
		double commande = erreur * 30;
		setSpeed(-commande, commande, robot);
		Sleep(100);
	}*/

	for (int i = 0; i < 100; i++) {
		odo.Update();
		odo.PrintData();
		double erreur = 15 - odo.getX();
		double commande = erreur * 5;
		setSpeed(commande, commande, robot);
		Sleep(100);
	}



	/*while (odo.getX() < 100) {
		setSpeed(40, 40, robot);
		Sleep(100);

		//maj odo
		odo.Update();
		odo.PrintData();

	}*/

	setSpeed(0, 0, robot);
	return 0;
}

