//
// Created by Топ3ДГрупп on 13.05.2022.
//

#include "EthernetModbusServer.h"

byte mac[] = {
        0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};
IPAddress ip(192, 168, 1, 20);

EthernetServer ethServer(502);

ModbusTCPServer modbusTCPServer;

extern bool firstSensorStatus;
extern bool secondSensorStatus;

void modbusSetup()
{
    //Ethernet.init(10);  // Most Arduino shields
    Serial.begin(9600);
    while (!Serial) {
        ; // wait for serial port to connect. Needed for native USB port only
    }
    Serial.println("Ethernet Modbus TCP Example");

    // start the Ethernet connection and the server:
    Ethernet.begin(mac, ip);

    // Check for Ethernet hardware present
    if (Ethernet.hardwareStatus() == EthernetNoHardware) {
        Serial.println("Ethernet shield was not found.  Sorry, can't run without hardware. :(");
        while (true) {
            delay(1); // do nothing, no point running without Ethernet hardware
        }
    }
    if (Ethernet.linkStatus() == LinkOFF) {
        Serial.println("Ethernet cable is not connected.");
    }
    // start the server
    ethServer.begin();

    // start the Modbus TCP server
    if (!modbusTCPServer.begin()) {
        Serial.println("Failed to start Modbus TCP Server!");
        while (1);
    }

    // configure the LED
    //pinMode(ledPin, OUTPUT);
    //digitalWrite(ledPin, HIGH);

    // configure a single coil at address 0x00
    //modbusTCPServer.setTimeout(1000);
    modbusTCPServer.configureCoils(0x00, 9);
    modbusTCPServer.configureHoldingRegisters(0x00, 9);
}

int coilValueStatus(uint8_t coilAdress)
{
    int coilValue = modbusTCPServer.coilRead(coilAdress);
    //long reg = modbusTCPServer.holdingRegisterRead(coilAdress);
    //Serial.print("reg: ");
    //Serial.println(reg);
    return coilValue;
}

void coilWriteFun(int address, uint8_t value)
{
    modbusTCPServer.coilWrite(address, value);
}


void modbusListen()
{
    //digitalWrite(ledPin, HIGH);

    // listen for incoming clients
    EthernetClient client = ethServer.available();

    if (client) {
        // a new client connected
        Serial.println("new client");

        // let the Modbus TCP accept the connection
        modbusTCPServer.accept(client);

        while (client.connected()) {
            // poll for Modbus TCP requests, while client connected
            modbusTCPServer.poll();

            // update the LED
            //updateLED();
            stepperWork();

            Serial.println("step 5s");
            delay(200);
        }

        Serial.println("client disconnected");
    }
    //delay(250);
}


