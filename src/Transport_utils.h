
#ifndef ASTROUART_TRANSPORT_UTILS_H
#define ASTROUART_TRANSPORT_UTILS_H

#include <vector>
#include <cstdint>

class Transport_utils {
public:
    static uint16_t compute_crc(uint8_t *p_data, uint8_t length);
    static std::vector<uint8_t> encode(std::vector<uint8_t> args);
    static std::vector<uint8_t> decode(std::vector<uint8_t> frame);
    static uint8_t ascii_offset(uint8_t byte);
    static uint8_t hex_offset(uint8_t byte);
    //TODO add CRC check function
};


#endif //ASTROUART_TRANSPORT_UTILS_H