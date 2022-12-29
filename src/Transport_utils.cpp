#include "Transport_utils.h"

#define COMMAND_CONTENT_MAX_SIZE 1024

// Control bytes
#define AI_START_BYTE 0x02 // The byte which indicates the beginning of a frame.
#define AI_END_BYTE   0x03 // The byte which indicates the end of a frame.

uint8_t Transport_utils::ascii_offset(uint8_t byte) {
    if (byte >= 0x30 && byte <= 0x39) {
        return 48;
    } else if (byte >= 0x41 && byte <= 0x46) {
        return 55;
    }
    return 0;
}

uint8_t Transport_utils::hex_offset(uint8_t byte) {
    if (byte <= 9) {
        return 48;
    } else if (byte >= 0xA && byte <= 0xF) {
        return 55;
    }
    return 0;
}

uint16_t Transport_utils::compute_crc(uint8_t *p_data, uint8_t length) {
    uint16_t x = 0;
    uint16_t crc = 0xFFFF;

    while (length--) {
        x = crc >> 8 ^ *p_data++;
        x ^= x >> 4;
        crc = (crc << 8) ^ (x << 12) ^ (x << 5) ^ (x);
    }
    return crc;
}

std::vector<uint8_t> Transport_utils::encode(std::vector<uint8_t> command) {
    uint8_t data[COMMAND_CONTENT_MAX_SIZE] = {0};
    std::copy(command.begin(), command.end(), data);
    int length = command.size();

    // add crc at the end
    uint16_t crc = Transport_utils::compute_crc(data, command.size());
    data[length++] = (uint8_t) crc;
    data[length++] = (uint8_t) (crc >> 8);

    std::vector<uint8_t> encoded;
    encoded.push_back(AI_START_BYTE);
    for (int i = 0; i < length; i++) {
        uint8_t first_digit = (uint8_t) data[i] >> 4;
        encoded.push_back(first_digit + hex_offset(first_digit));
        uint8_t last_digit = (uint8_t) data[i] & 0xF;
        encoded.push_back(last_digit + hex_offset(last_digit));
    }
    encoded.push_back(AI_END_BYTE);
    return encoded;
}

bool Transport_utils::is_answer_crc_valid( std::vector<uint8_t> decoded_answer){

    uint8_t data[COMMAND_CONTENT_MAX_SIZE] = {0};
    std::copy(decoded_answer.begin(), decoded_answer.end()-2, data);
    uint16_t computed_crc = Transport_utils::compute_crc(data, decoded_answer.size()-2);

    if(computed_crc == Transport_utils::get_command_crc(decoded_answer)){
        return true;
    }
    return false;
}

std::vector<uint8_t> Transport_utils::get_command_parameters(std::vector<uint8_t> decoded_answer){
    return {decoded_answer.begin() + 1, decoded_answer.end() - 2};
}

uint8_t Transport_utils::get_command_id(std::vector<uint8_t> decoded_answer){
    return decoded_answer.at(0);
}

uint16_t Transport_utils::get_command_crc(std::vector<uint8_t> decoded_answer){
    return decoded_answer.at(decoded_answer.size() - 1) << 8 | decoded_answer.at(decoded_answer.size() - 2);
}

std::vector<uint8_t> Transport_utils::decode(std::vector<uint8_t> encoded_answer) {
    std::vector<uint8_t> decoded;
    for (long unsigned int i = 0; i < encoded_answer.size(); i = i + 2) {
        uint8_t first_digit = (encoded_answer.at(i) - ascii_offset(encoded_answer.at(i))) << 4;
        uint8_t second_digit = encoded_answer.at(i + 1) - ascii_offset(encoded_answer.at(i + 1));
        decoded.push_back(first_digit + second_digit);
    }
    return decoded;
}

