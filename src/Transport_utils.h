
#ifndef ASTROUART_TRANSPORT_UTILS_H
#define ASTROUART_TRANSPORT_UTILS_H

#include <vector>
#include <cstdint>

class Transport_utils {
public:
    static uint16_t compute_crc(uint8_t *p_data, uint8_t length);
    static std::vector<uint8_t> encode(std::vector<uint8_t> command);
    static std::vector<uint8_t> decode(std::vector<uint8_t> encoded_answer);
    static uint8_t ascii_offset(uint8_t byte);
    static uint8_t hex_offset(uint8_t byte);
    static uint8_t get_command_id(std::vector<uint8_t> decoded_answer);
    static std::vector<uint8_t> get_command_parameters(std::vector<uint8_t> decoded_answer);
    static uint16_t get_command_crc(std::vector<uint8_t> decoded_answer);
    static bool is_answer_crc_valid( std::vector<uint8_t> decoded_answer);
};
#endif //ASTROUART_TRANSPORT_UTILS_H
