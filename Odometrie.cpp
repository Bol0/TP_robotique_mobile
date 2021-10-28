
#include "Odometrie.h"


Odometrie::Odometrie(WifibotClient *robot) {
	t_robot = robot;
	t_robot->GetSensorData(&t_sensors_data);
	t_odoLeft = 0;
	t_odoRight = 0;
	x = 0.0;
	y = 0.0;
	yaw = 0.0;
}

void Odometrie::Update() {
	t_robot->GetSensorData(&t_sensors_data);
	long buffLeft = t_sensors_data.OdometryLeft;
	long buffRight = t_sensors_data.OdometryRight;
	if (t_odoLeft == 0 && t_odoRight == 0) {
		t_odoLeft = buffLeft;
		t_odoRight = buffRight;
	}
	long tickLeft = buffLeft - t_odoLeft;
	long tickRight = buffRight - t_odoRight;
	t_odoLeft = buffLeft;
	t_odoRight = buffRight;
	double dist_l = ((double)tickLeft / 2048) * 2 * M_PI * rayonRoue;
	double dist_r = ((double)tickRight / 2048) * 2 * M_PI * rayonRoue;



	if (!(dist_l == 0 && dist_r == 0)) { //le robot n'est pas a l arret
		double dist = (dist_l + dist_r) / 2;
		double rayon = distanceRoue * (dist_r + dist_l) / (dist_r - dist_l);
		double diff_yaw = dist / rayon;

		//coordonees du centre du rayon de courbure
		double x0 = x - rayon * cos(yaw - (M_PI / 2));
		double y0 = y - rayon * sin(yaw - (M_PI / 2));

		//on maj les donnees
		if (dist_r == dist_l) { // rayon a l'infinie
			x += dist * cos(yaw);
			y += dist * sin(yaw);
		}
		else if (dist_r == -dist_l) { //rayon nul -> rotation pure
			yaw += (dist_r / distanceRoue);
		}
		else { //trajectoire normale selon un rayon de courbure
			yaw += diff_yaw;
			x = x0 + rayon * cos(yaw - (M_PI / 2));
			y = y0 + rayon * sin(yaw - (M_PI / 2));
		}

	}

}


void Odometrie::PrintData() {
	std::cout << "x : " << x << "\t y : " << y << "\t yaw : " << yaw << "\n";
}

double Odometrie::getX() {
	return x;
}

double Odometrie::getY() {
	return y;
}

double Odometrie::getYaw() {
	return yaw;
}