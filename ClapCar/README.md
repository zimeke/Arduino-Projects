# ClapCar

This project demonstrates how to control a small car using sound detection (clapping). By detecting different numbers of claps, the car can rotate or move forward. The use of LEDs provides visual feedback on the car’s status, making it easier to understand its current state.

The car responds to claps as follows:
* One clap: starts rotating to the right
* Two claps: starts rotating to the left
* Three claps: moves forward

If the car is moving (rotating or moving forward), a single clap will stop it.

The car’s movement is indicated by LEDs:
* Red LED: the car is stationary
* Green LED: the car is moving
* Yellow LED: indicates when a clap is detected

## Components Used
* Arduino Uno Rev3
* Motor Driver (L298N)
* 2 x DC Motor (JGA25-370; 12V 12rpm variant)
* Analog Sound Sensor
* 5.5mm DC Male Jack Connector
* 3 x 1kOhm Resistor
* 2 x 4AA Battery Holder
