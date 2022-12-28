#include <sstream>
#include <chrono>
#include <thread>
#include <future>

#include "Serial_hardware/SimpleSerial.h"
#include "Serial_fake/Serial_fake.h"
#include "Transport_layer.h"
#include "Transport_utils.h"
#include "Serial_port.h"

Transport_layer::Transport_layer(const std::string port) {
    port_ = port;
}

Transport_layer::serial_port_error_code_t Transport_layer::request_serial(Serial_port* sp, const std::vector<uint8_t> command, std::vector<uint8_t> * answer){
    std::cout << "Open port : " << port_ << std::endl;
    try {
        //convert to string
        std::string str(command.begin(), command.end());
        std::cout << "Transport::send: " << str << std::endl;
        //send
        sp->writeString(str);
        std::cout << "Transport::readline" << std::endl;


        // Lambda calling async readLine (threaded).
        std::future<std::vector<uint8_t>> future = std::async(std::launch::async, [&sp](){
            std::cout<<"future function"<<std::endl;
            return sp->readLine();
        });

        std::future_status status = future.wait_for(std::chrono::seconds(1));
        switch(status) {
            case std::future_status::timeout: std::cout << "timeout\n";
            return serial_port_error_code_t::TIMEOUT_ERROR;
            default:
                break;
        }   // TODO catch if timeout was raised, do something with it.
        *answer = future.get();
        return serial_port_error_code_t::NO_ERROR;
    }
    catch(boost::system::system_error& e)
    {
        std::cout<<"Error: "<<e.what()<<std::endl;
        answer->clear();
        return serial_port_error_code_t::NO_VALUE_ERROR;
    }
}

Transport_layer::answer_t Transport_layer::request_command(const std::vector<uint8_t> data){
    std::vector<uint8_t> encoded = Transport_utils::encode(data);
#ifdef FAKE_SERIAL
    Serial_fake serial(port_, BAUDRATE);
#else
    SimpleSerial serial(port_, BAUDRATE);
#endif
    std::vector<uint8_t> answer;
    uint8_t error_code = Transport_layer::request_serial(&serial, encoded, &answer);
    // TODO check that answer size is > 6 (ID + checksum)
    struct answer_t ans;
    if(answer.size() < 6){
        ans.error_code = NO_VALUE_ERROR;
        return ans;
    }
    std::vector<uint8_t> decoded_answer_ =  Transport_utils::decode(answer);

    if (error_code == Transport_layer::serial_port_error_code_t::NO_ERROR){
      //  ans.error_code = Transport_utils::is_answer_crc_valid(Transport_utils::get_command_parameters(decoded_answer_), Transport_utils::get_command_crc(decoded_answer_)) ? NO_ERROR : CRC_ERROR;
        ans.error_code = NO_ERROR;
    }
    else{
        ans.error_code = error_code;
    }

    ans.answer_parameters = Transport_utils::get_command_parameters(decoded_answer_);
    ans.answer_id = Transport_utils::get_command_id(decoded_answer_);
    ans.answer_checksum = Transport_utils::get_command_crc(decoded_answer_);
    return ans;
}
