#include <iostream>
#include "Serial_fake.h"
#include "Transport_utils.h"
#include "Opcodes_id.h"

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
    switch (command_id) {
        case ASTRONODE_OP_CODE_CFG_WR:
            answer_ = Transport_utils::encode({ASTRONODE_OP_CODE_CFG_WA});
            break;
        case ASTRONODE_OP_CODE_WIF_WR:
            answer_ = Transport_utils::encode({ASTRONODE_OP_CODE_WIF_WA});
            break;
        // TODO cases for all opcodes
        default:
            break;
    }
}

std::vector<uint8_t> Serial_fake::readLine() {
        std::cout<<"Serial fake readLine"<<std::endl;
        answer_.erase(answer_.begin());
        answer_.pop_back();
        return answer_;
}
