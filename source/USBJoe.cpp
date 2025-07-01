#include "../include/USBJoe.h"

USBJoe::USBJoe() {
    uint8_t error = openPort();

    if (error != 0) {
        std::cerr << "Failed to open USB port!" << std::endl;
    }
}

USBJoe::~USBJoe() {
    if (Serial.IsOpen()) {
        Serial.Close();
    }
}

uint8_t USBJoe::openPort() {
    try {
        Serial.Open("/dev/ttyACM0");
        Serial.SetBaudRate(LibSerial::BaudRate::BAUD_115200);
        Serial.SetCharacterSize(LibSerial::CharacterSize::CHAR_SIZE_8);
        Serial.SetStopBits(LibSerial::StopBits::STOP_BITS_1);
        Serial.SetParity(LibSerial::Parity::PARITY_NONE);
        Serial.SetFlowControl(LibSerial::FlowControl::FLOW_CONTROL_NONE);
    }
    catch (LibSerial::OpenFailed&) {
        std::cerr << "Failed to open port..." << std::endl;
        return 1;
    }

    return 0;
}

void USBJoe::sendCommand(const std::string& cmd) {
    if (!Serial.IsOpen()) {
        std::cerr << "Serial port not open!" << std::endl;
        return;
    }
    
    Serial.Write(cmd);

    std::cout << "Command sent!" << std::endl;

    std::this_thread::sleep_for(std::chrono::milliseconds(300));
}

void USBJoe::transmit(const std::vector<uint8_t>& data) {
    std::string cmd;

    for (size_t i = 0; i < data.size(); i++) {
        cmd += static_cast<char>(data[i]); 
    }

    sendCommand(cmd);
}

std::vector<uint8_t> USBJoe::receive() {
    std::vector<uint8_t> data;
    std::string payload;
    
    try {
        Serial.Read(payload, 8, 1000);
    } catch (const LibSerial::ReadTimeout&) {
        std::cerr << "Timeout: no data received in time." << std::endl;
        return {};
    }
    
    for (size_t i = 0; i < payload.size(); i++) {
        data.push_back(static_cast<uint8_t>(payload[i]));
    }
    
    return data;
}