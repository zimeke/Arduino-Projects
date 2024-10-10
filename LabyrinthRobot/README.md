# LabyrinthRobot

The LabyrinthRobot project involves creating a robot capable of navigating out of a maze. The robot first measures the distance in front of it using an ultrasonic sensor to determine how much space is available for movement. While moving forward, it continuously checks for a possible right turn. If it detects a right turn opportunity, the robot will turn right and restart the distance measurement process. If no right turn is found, it continues moving forward until it can no longer advance, at which point it will turn left and begin measuring the distance again.

## Components Used

* Arduino UNO rev3
* L298N Motor Driver
* 
