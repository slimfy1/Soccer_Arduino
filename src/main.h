//
// Created by slimfy1 on 13.05.2022.
//

#ifndef MAIN_H
#define MAIN_H

#define ENA 12 //Enable pin
#define DIR 11 //Direction pin
#define PUL 9 //Step pin

#define SENSOR_1_PIN 2 //First sensor pin
#define SENSOR_2_PIN 3 //Second sensor pin

#define MOTOR_STEPS 200
#define STEPPER_ANGLE_1 0
#define STEPPER_ANGLE_2 180
#define STEPPER_ANGLE_INIT 360



void stepperWork();

#endif //MAIN_H
