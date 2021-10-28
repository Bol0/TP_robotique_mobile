
#include "Odometrie.h"


Odometrie::Odometrie(WifibotClient &robot) {
	t_robot = robot;
	t_robot.GetSensorData(&t_sensors_data);
	t_odoLeft = t_sensors_data.OdometryLeft;
	t_odoRight = t_sensors_data.OdometryRight;
	x = 0.0;
	y = 0.0;
	yaw = 0.0;
}

void Odometrie::Update() {
	t_robot.GetSensorData(&t_sensors_data);
	long tickLeft = t_sensors_data.OdometryLeft - t_odoLeft;
	long tickRight = t_sensors_data.OdometryRight - t_odoRight;
	t_odoLeft = t_sensors_data.OdometryLeft;
	t_odoRight = t_sensors_data.OdometryRight;
	long dist_l = (tickLeft / 2048) * 2 * M_PI * rayonRoue;
	long dist_r = (tickRight / 2048) * 2 * M_PI * rayonRoue;



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