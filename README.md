# Terrace-Farming-Robot

## Abstract
The terrace farming done in hilly areas is not properly mechanized and a lot of challenges are faced by the farmers. To overcome these problems, an autonomous robot can serve as a boon. The aim of our team is to design and build a light-weight robot that can be used for terrace farming in areas having hilly terrain

## Aim
* All-in-one solution for various farming requirments
* perform agricultural tasks in all weather conditions
* reduced or no human involvement


## Design

* The mechanism is inspired by Forklift in order to facilitate faster and efficient climbing on th eterrace steps.
* Body of the robot is devided into three components.
* The robot can perform ploughing, seeding and watering. 

## Working
Initially the front part is raised to the required step height. Then the main compartment of the robot, as well as the whole body moves closer to the step making the part which is raised, to land on the upper step. The front and the rear lead screws rotate in opposite sense so as to lift the middle compartment. When it gains required height the robot again moves closer to the walls and the middle component also climbs up the immediate step. Now, when the front and middle segments have successfully landed on the upper step, the rear lead screws are again rotated to lift the rear part. This process is repeated to climb up the stairs. When the robot is on the stairs the tyres helps in easy maneuvering. The vacant pace provided in the middle compartment can be installed with different mechanisms to do different farming activities. 

## Poster
!["Poster"](https://github.com/Kartik-Aggarwal/Terrace-Farming-Robot/blob/main/images/Poster.png)

## Automation

Automation is achieved using a combination of IR sensors, ultrasonic sensors and proximity sensors using Arduino Uno as the microcontroller.\
Sovel Feldman edge detection is used to feed the data of edges along with the depth sensing data from the sensors to automate the navigation

!["App"](https://github.com/Kartik-Aggarwal/Terrace-Farming-Robot/blob/main/images/app.jpeg)

## Prototype
!["Poster"](https://github.com/Kartik-Aggarwal/Terrace-Farming-Robot/blob/main/images/robot.jpeg)
