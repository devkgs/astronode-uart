#include <iostream>

#include "Serial_fake.h"
#include "Transport_utils.h"
#include "Opcodes_id.h"

#include <unistd.h>

Serial_fake::Serial_fake(__attribute__((unused)) std::string port, __attribute__((unused)) unsigned int baud_rate){
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
        case ASTRONODE_OP_CODE_CFG_RR:
            answer_ = Transport_utils::encode({ASTRONODE_OP_CODE_CFG_RA, 1, 2, 3, 4, 5, 6, 7, 8});
            break;
        case ASTRONODE_OP_CODE_WIF_WR:
            answer_ = Transport_utils::encode({ASTRONODE_OP_CODE_WIF_WA});
            break;
        case ASTRONODE_OP_CODE_SSC_WR:
            answer_ = Transport_utils::encode({ASTRONODE_OP_CODE_SSC_WA});
            break;
        // TODO cases for all opcodes
        default:
            //answer_id += 0x80;
            std::cout<<"error unknown opcode: 0x"  << command_id <<std::endl;
            answer_ = Transport_utils::encode({0xff/*answer_id*/});    //TODO add error code
            break;
    }
}

std::vector<uint8_t> Serial_fake::readLine() {
        //usleep(2*1000*1000);  // for timeout testing
        std::cout<<"Serial fake readLine"<<std::endl;
        answer_.erase(answer_.begin());
        answer_.pop_back();
        return answer_;
}
