#include <sstream>
#include <chrono>
#include <thread>
#include <future>

#include "Serial_hardware/SimpleSerial.h"
#include "Serial_fake/Serial_fake.h"
#include "Transport_layer.h"
#include "Transport_utils.h"

Transport_layer::Transport_layer(const std::string port) {
    port_ = port;
}

std::vector<uint8_t> Transport_layer::request_serial(const std::vector<uint8_t> command, std::vector<uint8_t> * answer){
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

        return serial.readLine();

        // Lambda calling async readLine (threaded).
        /*std::future<std::vector<uint8_t>> future = std::async(std::launch::async, [&serial](){
            std::cout<<"futur function"<<std::endl;
            return serial.readLine();
        });

        std::future_status status = future.wait_for(std::chrono::seconds(1));
        switch(status) {
           // case std::future_status::deferred: std::cout << "deferred\n"; break;
            case std::future_status::timeout: std::cout << "timeout\n"; break;
           // case std::future_status::ready: std::cout << "ready!\n"; break;
            default:
                break;
        }   // TODO catch if timeout was raised, do something with it.

        return future.get();*/
    }
    catch(boost::system::system_error& e)
    {
        std::cout<<"Error: "<<e.what()<<std::endl;
        return command;
    }
    answer->push_back(1);
}

Transport_layer::answer_t Transport_layer::request_command(const std::vector<uint8_t> data){
    std::vector<uint8_t> encoded = Transport_utils::encode(data);
    std::vector<uint8_t> answw;
    std::vector<uint8_t> answer = Transport_layer::request_serial(encoded, &answw);
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
