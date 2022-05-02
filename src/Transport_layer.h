#ifndef ASTROUART_TRANSPORT_LAYER_H
#define ASTROUART_TRANSPORT_LAYER_H

#include <cstdint>
#include <iostream>
#include <memory>
#include <vector>

#include "SerialInterface.h"

#define BAUDRATE 9600

class Transport_layer {
public:
    Transport_layer(const std::string port);

    struct Command_t{
        uint8_t command_id;
        std::vector<uint8_t> command_parameters;
        std::vector<uint8_t> command_checksum;
        uint8_t error_code;
    };

    typedef enum serial_error_code
    {
        NO_ERROR                = 0,
        OPEN_PORT_FAILURE       = 1,
        TIMEOUT_ERROR           = 2,
        CRC_ERROR               = 3
    }serial_error_code_t;

    virtual Command_t request_command(const std::vector<uint8_t> command);

private:
     std::vector<uint8_t> request_serial(const std::vector<uint8_t> command);
    std::string port_;
};
#endif //ASTROUART_TRANSPORT_LAYER_H
