#ifndef ASTROUART_TRANSPORT_LAYER_H
#define ASTROUART_TRANSPORT_LAYER_H

#include <cstdint>
#include <iostream>
#include <memory>
#include <vector>

#include "Opcodes_id.h"

#define BAUDRATE 9600

class Transport_layer {
public:
    Transport_layer(const std::string port);

    struct answer_t{
        uint8_t answer_id;
        std::vector<uint8_t> answer_parameters;
        std::vector<uint8_t> answer_checksum;
        uint8_t error_code;
    };

    virtual answer_t request_command(const std::vector<uint8_t> command);
    std::vector<uint8_t> request_serial(const std::vector<uint8_t> command);
private:

    std::string port_;
};
#endif //ASTROUART_TRANSPORT_LAYER_H
