#include "Transport_layer.h"
#include <sstream>
#include "SimpleSerial.h"
#include <memory>
#include "Transport_utils.h"

std::vector<uint8_t> Transport_layer::request_serial(const std::vector<uint8_t> command) {
    //open port
    std::cout << "Open port : " << SERIAL_PORT << std::endl;
    SimpleSerial serial(SERIAL_PORT, BAUDRATE);
    //convert to string
    std::string str(command.begin(), command.end());
    std::cout<<"send: "<<str<<std::endl;
    //send
    serial.writeString(str);
    std::cout<<"readline"<<std::endl;

    return serial.readLine();
    /*
      } catch(boost::system::system_error& e)
    {
        cout<<"Error: "<<e.what()<<endl;
        return 1;
    }
     */
}

Transport_layer::Command_t Transport_layer::request_command(const std::vector<uint8_t> data){
    std::cout<<"sending forced_to_be_override"<<std::endl;
    std::vector<uint8_t> encoded = Transport_utils::encode(data);
    std::vector<uint8_t> answer = Transport_layer::request_serial(encoded);
    std::vector<uint8_t> decoded_answer_ =  Transport_utils::decode(answer);
    struct Command_t ans;
    ans.command_parameters = Transport_utils::get_command_parameters(decoded_answer_);
    ans.command_id = Transport_utils::get_command_id(decoded_answer_);
    ans.command_checksum = Transport_utils::get_command_crc(decoded_answer_);
    return ans;
}
