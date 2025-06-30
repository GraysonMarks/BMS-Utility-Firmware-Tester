#include <boost/algorithm/string.hpp>

#include "../include/BMSUtilityGuy.h"

void BMSUtilityGuy::talk(std::vector<uint8_t>& data) {
    joe.transmit(data);
}

std::vector<uint8_t> BMSUtilityGuy::listen() {
    return joe.receive();
}

std::vector<uint8_t> BMSUtilityGuy::preparePayloadBytes(std::string payload) {
    std::vector<std::string> hexStrs;
    std::vector<uint8_t> bytes(8, 0);
    
    boost::split(hexStrs, payload, boost::is_any_of(","));

    for (size_t i = 0; i < hexStrs.size(); i++) {
        bytes[i] = std::stoi(hexStrs[i], 0, _HEX_);
    }
    
    return bytes;
}