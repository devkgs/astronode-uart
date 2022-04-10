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

void Transport_layer::request_command(const std::vector<uint8_t> data){
    std::cout<<"sending forced_to_be_override"<<std::endl;
    std::vector<uint8_t> encoded = Transport_utils::encode(data);
    std::vector<uint8_t> answer = Transport_layer::request_serial(encoded);
    decoded_answer_ =  Transport_utils::decode(answer);
}
/* example answer to cfg_r
 2,   39,35, ....,   37,32,37,30, 3
 stx, code, content, checksum,    etx

 2
39
35
30
34
30
31
30
32
30
38
30
31
30
35
30
30
30
35
37
32
37
30
3
 */

bool Transport_layer::get_answer_success(void){
    return true;
}

std::vector<uint8_t> Transport_layer::get_answer_parameters(void){
    return decoded_answer_;
}


