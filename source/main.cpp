#include "../include/BMSUtilityGuy.h"

int main(int argc, char** argv) {
    std::vector<uint8_t> tx(8, 0);
    std::vector<uint8_t> rx;

    if (argc != 3) {
        std::cerr << "Invalid input!" << std::endl;
        return -1;
    }

    if (std::string(argv[1]) == "-c") {
        tx = BMSUtilityGuy::getBMSUtilityGuy().preparePayloadBytes(argv[2]);

        for (uint16_t count = 0; count < 1; count++) {
            BMSUtilityGuy::getBMSUtilityGuy().talk(tx);
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            
            rx = BMSUtilityGuy::getBMSUtilityGuy().listen();
            
            std::cout << "Data: ";
            for (size_t i = 0; i < rx.size(); i++) {
                std::cout << std::setfill('0') << std::setw(2) <<
                std::hex << std::uppercase << (int)rx[i] << " ";
            }
            std::cout << std::endl << std::endl;

            if (rx[0] == 0x05) {
                return 0;
            }

            // for (size_t i = 0; i < rx.size(); i += 2) {
            //     uint8_t LSB = static_cast<uint8_t>(rx[i + 1]);
            //     uint8_t MSB = static_cast<uint8_t>(rx[i]);
            
            //     uint16_t result = (MSB << 8) | LSB;
                
            //     float number = static_cast<float>(result);

            //     std::cout << number << " ";
            // }
            // std::cout << std::endl;

            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        }     
    }
    else {
        std::cerr << "Invalid input!" << std::endl;
        return -1;
    }

    return 0;
}