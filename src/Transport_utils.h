
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
    static uint8_t get_command_id(std::vector<uint8_t> decoded_frame);
    static std::vector<uint8_t> get_command_parameters(std::vector<uint8_t> decoded_frame);
    static std::vector<uint8_t> get_command_crc(std::vector<uint8_t> decoded_frame);
 //   static uint16_t calculate_crc(std::vector<uint8_t> data, uint16_t data_len, uint16_t init_value);
    static bool is_answer_crc_valid(std::vector<uint8_t> decoded_frame, uint16_t expected_crc);
};


#endif //ASTROUART_TRANSPORT_UTILS_H
