#include <memory>
#include <sstream>

#include "Serial_hardware/SimpleSerial.h"
#include "Serial_fake/Serial_fake.h"
#include "Transport_layer.h"
#include "Transport_utils.h"

Transport_layer::Transport_layer(const std::string port) {
    port_ = port;
}

std::vector<uint8_t> Transport_layer::request_serial(const std::vector<uint8_t> command){
    //open port
    std::cout << "Open port : " << port_ << std::endl;
    try {
#ifdef FAKE_SERIAL
        Serial_fake serial(port_, BAUDRATE);
#else
        SimpleSerial serial(port_, BAUDRATE);
#endif
        //convert to string
        std::string str(command.begin(), command.end());
        std::cout << "Transport::send: " << str << std::endl;
        //send
        serial.writeString(str);
        std::cout << "Transport::readline" << std::endl;

        //read answer
        return serial.readLine();
    }
    catch(boost::system::system_error& e)
    {
        std::cout<<"Error: "<<e.what()<<std::endl;
        return command;
    }
}

Transport_layer::answer_t Transport_layer::request_command(const std::vector<uint8_t> data){
    std::vector<uint8_t> encoded = Transport_utils::encode(data);
    std::vector<uint8_t> answer = Transport_layer::request_serial(encoded);
    // TODO check that answer size is > 6 (ID + checksum)
    struct answer_t ans;
    if(answer.size() < 6){
        ans.error_code = NO_VALUE_ERROR;
        return ans;
    }
    std::vector<uint8_t> decoded_answer_ =  Transport_utils::decode(answer);

    ans.answer_parameters = Transport_utils::get_command_parameters(decoded_answer_);
    ans.answer_id = Transport_utils::get_command_id(decoded_answer_);
    ans.answer_checksum = Transport_utils::get_command_crc(decoded_answer_);
    ans.error_code = Transport_utils::is_answer_crc_valid(decoded_answer_) ? NO_ERROR : CRC_ERROR;
    return ans;
}
