# LabyrinthRobot

The LabyrinthRobot project involves creating a robot capable of navigating out of a maze. The robot first measures the distance in front of it using an ultrasonic sensor to determine how much space is available for movement. While moving forward, it continuously checks for a possible right turn. If it detects a right turn opportunity, the robot will turn right and restart the distance measurement process. If no right turn is found, it continues moving forward until it can no longer advance, at which point it will turn left and begin measuring the distance again.

![LabyrinthRobot](https://github.com/user-attachments/assets/c0fd9e2e-76c2-4d62-8cd9-c5b683e22a94)


![Schematic](https://github.com/user-attachments/assets/61cdb3bb-d1bb-450b-9666-6f9bca4156af)

## Components Used
* Arduino Uno Rev3
* Motor Driver (L298N)
* 2 x DC Motor (JGA25-370; 12V 12rpm variant)
* Ultrasonic Sensor (HC-SR04)
* 5.5mm DC Male Jack Connector
* Servo Motor (SG90)
* 2 x 4AA Battery Holder
* Chassis: A custom-built frame where the components are mounted on a wooden board, along with a support wheel for stability
