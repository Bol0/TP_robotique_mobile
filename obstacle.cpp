int checkWall() {  // return 0 if none, 1 if obstacle is located at the left of the bot, 2 if at right and 3 if obstacle is at front
	SensorData sensors_data;
	
	robot.GetSensorData(&sensors_data);
	
	int distLeft = sensors_data.IRLeft();
	int distRight = sensors_data.IRRight();
	distRight = SharpLUT[distRight];
	distLeft = SharpLUT[distLeft];
	
	
	
	if (distLeft<=35 && distRight<=35) return 3;   // threshold at 35cm
	else if (distLeft<=35) return 1;
	else if (distRight<=35) return 2;
	
	return 0;

}

void travel() {
	int event = checkWall();
	Odometrie.update();
	double y = Odometrie.getY();
	double x = Odometrie.getX();
	double yaw = Odometrie.getYaw();
	if(event==0 && !moving && y>=-deltaY && y<=deltaY) { 
			moving = true;
			slow=false;
			robot.SendCommand(150,150);
	}
	else if (event==1 && !slow) {
		slow=true;
		robot.SendCommand(70,70);
	}
	else if (event==1 && slow) {
		obstacleAvoid(1);
		slow=false;
	}
	else if (event==2 && !slow) {
		slow=true;
		robot.SendCommand(70,70);
	}
	else if (event==2 && slow) {
		obstacleAvoid(2);
		slow=false;
	}
	else if (event==3 && !slow) {
		slow=true;
		robot.SendCommand(70,70);
	}
	else if (event==3 && slow) {
		obstacleAvoid(3);
		slow=false;
	}
	if (y<-deltaY || y>deltaY) obstacleAvoid(0);
	
	if(x==1000) {
		robot.SendCommand(0,0);
		while(1);
	}
	
	
}

void obstacleAvoid(int eventType) {
	robot.SendCommand(0,0);
	Odometrie.update();
	double y = Odometrie.getY();
	double x = Odometrie.getX();
	double yaw = Odometrie.getYaw();
	if (eventType==0) {
		if (y<-deltaY) {
			actYaw = yaw;
			robot.SendCommand(0,-70);
			while(yaw<actYaw+90.0) {
				Odometrie.update();
				yaw = Odometrie.getYaw();
			}
			robot.SendCommand(70,70);
			while(y<-8.0) {
				Odometrie.update();
				y = Odometrie.getY();
			}
			robot.SendCommand(0,70);
			while(yaw>0.0) {
				Odometrie.update();
				yaw = Odometrie.getYaw();
			}
		}
		
		else{
			actYaw = yaw;
			robot.SendCommand(-70,0);
			while(yaw>actYaw-90.0) {
				Odometrie.update();
				yaw = Odometrie.getYaw();
			}
			robot.SendCommand(70,70);
			while(y>8.0) {
				Odometrie.update();
				y = Odometrie.getY();
			}
			robot.SendCommand(70,0);
			while(yaw<0.0) {
				Odometrie.update();
				yaw = Odometrie.getYaw();
			}
		}
		
	}
	
	else if(eventType==1 && y<deltaY) {
		actYaw = yaw;
		robot.SendCommand(0,-70);
		while(yaw<actYaw+90.0) {
			Odometrie.update();
			yaw = Odometrie.getYaw();
		}
		robot.SendCommand(70,70);
		while(y<deltaY) {
			Odometrie.update();
			y = Odometrie.getY();
		}
		robot.SendCommand(-70,0);
		while(yaw>0.0) {
			Odometrie.update();
			yaw = Odometrie.getYaw();
		}
	}
	
	else if(eventType==1 && y>=deltaY) {
		actYaw = yaw;
		robot.SendCommand(-70,0);
		while(yaw>actYaw-90.0) {
			Odometrie.update();
			yaw = Odometrie.getYaw();
		}
		robot.SendCommand(70,70);
		while(y>-deltaY) {
			Odometrie.update();
			y = Odometrie.getY();
		}
		robot.SendCommand(0,-70);
		while(yaw<0.0) {
			Odometrie.update();
			yaw = Odometrie.getYaw();
		}
	}
	
	else if (eventType==2 && y>-deltaY) {
		actYaw = yaw;
		robot.SendCommand(-70,0);
		while(yaw>actYaw-90.0) {
			Odometrie.update();
			yaw = Odometrie.getYaw();
		}
		robot.SendCommand(70,70);
		while(y>-deltaY) {
			Odometrie.update();
			y = Odometrie.getY();
		}
		robot.SendCommand(0,-70);
		while(yaw<0.0) {
			Odometrie.update();
			yaw = Odometrie.getYaw();
		}
	}
	
	else if (eventType==2 && y<=-deltaY) {
		actYaw = yaw;
		robot.SendCommand(0,-70);
		while(yaw<actYaw+90.0) {
			Odometrie.update();
			yaw = Odometrie.getYaw();
		}
		robot.SendCommand(70,70);
		while(y<deltaY) {
			Odometrie.update();
			y = Odometrie.getY();
		}
		robot.SendCommand(-70,0);
		while(yaw>0.0) {
			Odometrie.update();
			yaw = Odometrie.getYaw();
		}
	}
	
	else if(eventType==3) {
		if(y<0.0) {
			actYaw = yaw;
			robot.SendCommand(0,-70);
			while(yaw<actYaw+90.0) {
				Odometrie.update();
				yaw = Odometrie.getYaw();
			}
			robot.SendCommand(70,70);
			while(y<deltaY) {
				Odometrie.update();
				y = Odometrie.getY();
			}
			robot.SendCommand(-70,0);
			while(yaw>0.0) {
				Odometrie.update();
				yaw = Odometrie.getYaw();
			}
		}
		else {
			actYaw = yaw;
			robot.SendCommand(-70,0);
			while(yaw>actYaw-90.0) {
				Odometrie.update();
				yaw = Odometrie.getYaw();
			}
			robot.SendCommand(70,70);
			while(y>-deltaY) {
				Odometrie.update();
				y = Odometrie.getY();
			}
			robot.SendCommand(0,-70);
			while(yaw<0.0) {
				Odometrie.update();
				yaw = Odometrie.getYaw();
			}
			
		}
	
	}
	robot.SendCommand(0,0);
	moving=false;
	return;
}
