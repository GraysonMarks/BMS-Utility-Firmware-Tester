#ifndef USBJOE_H
#define USBJOE_H

#include <iostream>
#include <vector>
#include <thread>
#include <chrono>

#include <libserial/SerialPort.h>

class USBJoe {
private:
    LibSerial::SerialPort Serial;

    uint8_t openPort();
    void sendCommand(const std::string& cmd);

public:
     USBJoe();
    ~USBJoe();

    void transmit(const std::vector<uint8_t>& data);
    std::vector<uint8_t> receive();
};

#endif