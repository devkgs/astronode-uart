#ifndef ASTROUART_TRANSPORT_H
#define ASTROUART_TRANSPORT_H

#include <vector>
#include <cstdint>
#include <iostream>
#include <memory>
#include "SerialInterface.h"

#define SERIAL_PORT "/dev/ttyUSB3"
#define BAUDRATE 9600

class Transport {
public:
    virtual void request_command(const std::vector<uint8_t> command);
    virtual bool get_answer_success(void);
    virtual std::vector<uint8_t> get_answer_parameters(void);
private:
    static std::vector<uint8_t> request_serial(const std::vector<uint8_t> command);
    static uint16_t compute_crc(uint8_t *p_data, uint8_t length);
    static std::vector<uint8_t> encode(std::vector<uint8_t> args);
    static std::vector<uint8_t> decode(std::vector<uint8_t> frame);
    static uint8_t ascii_offset(uint8_t byte);
    static uint8_t hex_offset(uint8_t byte);
    std::vector<uint8_t> decoded_answer_;
    std::shared_ptr<SerialInterface> si_;
};
#endif //ASTROUART_TRANSPORT_H
