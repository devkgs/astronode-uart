
#ifndef ASTROUART_COMMAND_H
#define ASTROUART_COMMAND_H

#include <vector>
#include <cstdint>

typedef struct command_t{
    uint8_t command_id;
    std::vector<uint8_t> command_parameters;
    uint16_t command_checksum;

} command_t;

#endif //ASTROUART_COMMAND_H
