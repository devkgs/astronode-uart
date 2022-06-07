#include <iostream>
#include "Serial_fake.h"
#include "Transport_utils.h"

Serial_fake::Serial_fake(std::string port, unsigned int baud_rate){
    std::cout<<"Serial fake constructor"<<std::endl;
}

void Serial_fake::writeString(std::string request) {
    std::cout<<"Serial fake writeString: "<<request<<std::endl;
    std::vector<uint8_t> v(request.begin(), request.end());

    // remove stx and etx
    v.erase(v.begin());
    v.pop_back();
    std::vector<uint8_t> decoded_answer_ =  Transport_utils::decode(v);
    uint8_t command_id = Transport_utils::get_command_id(decoded_answer_);
   // command_id += 0x80;
  //  std::vector<uint8_t> answer = {command_id};
    switch (command_id) {
        case 0x05:
//            answer_ = {0x85};//, 0xDD, 0x20};
            answer_ = Transport_utils::encode({0x85});
            break;
        case 0x06:
            break;
        case 0x07:
            break;
        default:
            break;
    }
}

std::vector<uint8_t> Serial_fake::readLine() {
        std::cout<<"Serial fake readLine"<<std::endl;
        answer_.erase(answer_.begin());
        answer_.pop_back();
       // std::vector<uint8_t> result = {0x12, 0x34, 0x55, 0x33, 0x44, 0x55};
        return answer_;
}

//std::vector<uint8_t> Serial_fake::fake_cfg_w(void){
//
//}