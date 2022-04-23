#ifndef ASTROUART_TRANSPORT_LAYER_H
#define ASTROUART_TRANSPORT_LAYER_H

#include <vector>
#include <cstdint>
#include <iostream>
#include <memory>
#include "SerialInterface.h"

#define SERIAL_PORT "/dev/ttyUSB3"
#define BAUDRATE 9600

class Transport_layer {
public:
   /* typedef struct t_answer{
        std::vector<uint8_t> params;
        bool sucess;
    } t_answer;
*/
    virtual std::vector<uint8_t> request_command(const std::vector<uint8_t> command);
//    std::vector<uint8_t> request_command(const std::vector<uint8_t> command);
    virtual bool get_answer_success(void);
    virtual std::vector<uint8_t> get_answer_parameters(void);
   // enum answer_return_codes {};
    typedef enum serial_error_code
    {
        NO_ERROR                = 0,
        OPEN_PORT_FAILURE       = 1,
        TIMEOUT_ERROR           = 2
    }serial_error_code_t;
private:
    static std::vector<uint8_t> request_serial(const std::vector<uint8_t> command);
 //   static uint16_t compute_crc(uint8_t *p_data, uint8_t length);
 //   static std::vector<uint8_t> encode(std::vector<uint8_t> args);
  //  static std::vector<uint8_t> decode(std::vector<uint8_t> frame);
  //  static uint8_t ascii_offset(uint8_t byte);
  //  static uint8_t hex_offset(uint8_t byte);
    std::vector<uint8_t> decoded_answer_;
};
#endif //ASTROUART_TRANSPORT_LAYER_H
