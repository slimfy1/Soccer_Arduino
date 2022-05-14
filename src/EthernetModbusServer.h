//
// Created by Топ3ДГрупп on 13.05.2022.
//

#ifndef ETHERNETMODBUSSERVER_H
#define ETHERNETMODBUSSERVER_H

#include <SPI.h>
#include <Ethernet.h>
#include "main.h"
#include <ArduinoRS485.h> // ArduinoModbus depends on the ArduinoRS485 library
#include <ArduinoModbus.h>
#include "Arduino.h"

void modbusSetup();
void modbusListen();
int coilValueStatus(uint8_t coilAdress);
void coilWriteFun(int address, uint8_t value);

#endif //ETHERNETMODBUSSERVER_H
