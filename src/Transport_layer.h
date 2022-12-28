#ifndef ASTROUART_TRANSPORT_LAYER_H
#define ASTROUART_TRANSPORT_LAYER_H

#include <cstdint>
#include <iostream>
#include <memory>
#include <vector>

#include "Opcodes_id.h"
#include "Serial_port.h"
#include "Transport_layer.h"

#define BAUDRATE 9600

class Transport_layer {
public:
    Transport_layer(const std::string port);

    struct answer_t{
        uint8_t answer_id;
        std::vector<uint8_t> answer_parameters;
        std::vector<uint8_t> answer_checksum;
        uint8_t error_code; // serial port error code
    };

    typedef enum serial_port_error_code
    {
        NO_ERROR                = 0,
        OPEN_PORT_FAILURE       = 1,
        TIMEOUT_ERROR           = 2,
        CRC_ERROR               = 3,
        NO_VALUE_ERROR          = 4,
        NO_REQUEST_SENT         = 5
    }serial_port_error_code_t;

    virtual answer_t request_command(const std::vector<uint8_t> command);
    serial_port_error_code_t request_serial(Serial_port* sp, const std::vector<uint8_t> command, std::vector<uint8_t> * answer);
private:
    std::string port_;
};
#endif //ASTROUART_TRANSPORT_LAYER_H
