#include <Arduino.h>
#include "A4988.h"
#include "main.h"
#include "EthernetModbusServer.h"

A4988 stepper(MOTOR_STEPS, DIR, PUL);

#define OPEN_GATE stepper.rotate(STEPPER_ANGLE_1)
#define CLOSE_GATE stepper.rotate(STEPPER_ANGLE_2)
#define INITE_POSE_GATE stepper.rotate(STEPPER_ANGLE_INIT)

bool firstSensorStatus;
bool secondSensorStatus;

bool stepperOpenStatus = false;
bool stepperCloseStatus = true;

void firstSensorInterrupt()
{
    while (!digitalRead(SENSOR_1_PIN))
    {
        firstSensorStatus = true;
        coilWriteFun(0x00, 0x00);
        Serial.println("Sensor 1 true");
        break;
    }

    while (digitalRead(SENSOR_1_PIN))
    {
        firstSensorStatus = false;
        coilWriteFun(0x00, 0x01);
        Serial.println("Sensor 1 false");
        break;
    }
}

void secondSensorInterrupt()
{
    while (!digitalRead(SENSOR_2_PIN))
    {
        firstSensorStatus = false;
        coilWriteFun(0x01, 0x00);
        Serial.println("Sensor 2 false");
        break;
    }

    while (digitalRead(SENSOR_2_PIN))
    {
        firstSensorStatus = true;
        coilWriteFun(0x01, 0x01);
        Serial.println("Sensor 2 true");
        break;
    }
}

void stepperWork()
{

    if(stepperOpenStatus)
    {
        coilWriteFun(0x02, 0x01);
    }
    if(!stepperOpenStatus)
    {
        coilWriteFun(0x02, 0x00);
    }

    if(stepperCloseStatus)
    {
        coilWriteFun(0x03, 0x01);
    }
    if(!stepperCloseStatus)
    {
        coilWriteFun(0x03, 0x00);
    }

    int coilValue = coilValueStatus(0x04);
    Serial.println(stepperCloseStatus);
    Serial.println(stepperOpenStatus);
    while ((coilValue == 1) && stepperCloseStatus)
    {
        // coil value set, turn LED on
        Serial.println("Open ball gate");
        stepperCloseStatus = false;
        stepperOpenStatus = true;
        OPEN_GATE;
        break;
    }

    while ((coilValue == 0) && stepperOpenStatus)
    {
        // coil value set, turn LED on
        Serial.println("Close ball gate");
        stepperCloseStatus = true;
        stepperOpenStatus = false;
        OPEN_GATE;
        break;
    }

}
void setup()
{
    modbusSetup();
    //Sensor block
    pinMode(SENSOR_1_PIN, INPUT_PULLUP);
    pinMode(SENSOR_2_PIN, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(SENSOR_1_PIN), firstSensorInterrupt, CHANGE);
    attachInterrupt(digitalPinToInterrupt(SENSOR_2_PIN), secondSensorInterrupt, CHANGE);
    //Stepper block
    pinMode(ENA, OUTPUT);
    stepper.begin(50, 16);
    INITE_POSE_GATE;
// write your initialization code here
}

void loop()
{
    //modbusListen();
    modbusListen();

    //OPEN_GATE;
    //delay(1000);
    //CLOSE_GATE;
    //delay(1000);
// write your code here
}