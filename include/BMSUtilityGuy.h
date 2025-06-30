#ifndef BMSUTILITYGUY_H
#define BMSUTILITYGUY_H

#include <iostream>
#include <iomanip>

#include "../include/USBJoe.h"

#define _HEX_ 16

class BMSUtilityGuy {
private:
    static BMSUtilityGuy sBMSUtilityGuy_;
    
    USBJoe joe;

public:
    static BMSUtilityGuy& getBMSUtilityGuy() { return sBMSUtilityGuy_; }

     BMSUtilityGuy() = default;
    ~BMSUtilityGuy() = default;

    void talk(std::vector<uint8_t>& data);
    std::vector<uint8_t> listen();
    
    std::vector<uint8_t> preparePayloadBytes(std::string payload);
};

inline BMSUtilityGuy BMSUtilityGuy::sBMSUtilityGuy_;

#endif