WifiBot Esigelec team 1A repository
===================================
Autonomous navigation project based on wifibot.
Only `odometry`, `infrared proximity sensors` and `camera` are allowed.

Class definition
================
WifiBotClient
-------------
Basic API allowing to communicate with the robot, and to get its values.

Odometrie
---------
This class allows us to know the position of the robot according to its odometry. 
Use the Update() function to update it as often as possible.
You can then retrieve the position of the robot by calling the getX(), getY() and getYaw() functions to get the absolute position and orientation of the robot with respect to its starting point.

PID
---
Not implemented yet but it will be a simple PID command.

Project participants
====================
LAROCHE Corentin <corentin.laroche@groupe-esigelec.org>
LE GUEN Yoann <Yoannleguen56@gmail.com>
DANNIEL Erwan <Erwan.denniel@gmail.com>
Sorry for the last one <UwU.com>