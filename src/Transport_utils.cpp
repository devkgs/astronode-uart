#include "Transport_utils.h"
#include "Command.h"

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

std::vector<uint8_t> Transport_utils::encode(std::vector<uint8_t> args) {
    uint8_t data[COMMAND_CONTENT_MAX_SIZE] = {0};
    std::copy(args.begin(), args.end(), data);
    int length = args.size();

    // add crc at the end
    uint16_t crc = Transport_utils::compute_crc(data, args.size());
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

bool Transport_utils::answer_frame_verification(std::vector<uint8_t> decoded_frame){
    return false;
}

std::vector<uint8_t> Transport_utils::get_command_parameters(std::vector<uint8_t> decoded_frame){
    return {decoded_frame.begin() + 1, decoded_frame.end() - 2};
}

uint8_t Transport_utils::get_command_id(std::vector<uint8_t> decoded_frame){
    return decoded_frame.at(0);
}

std::vector<uint8_t> Transport_utils::get_command_crc(std::vector<uint8_t> decoded_frame){
    return {decoded_frame.end() - 2, decoded_frame.end()};
}

std::vector<uint8_t> Transport_utils::decode(std::vector<uint8_t> frame) {
    std::vector<uint8_t> decoded;
    for (int i = 0; i < frame.size(); i = i + 2) {
        uint8_t first_digit = (frame.at(i) - ascii_offset(frame.at(i))) << 4;
        uint8_t second_digit = frame.at(i + 1) - ascii_offset(frame.at(i + 1));
        decoded.push_back(first_digit + second_digit);
    }
    return decoded;
}

