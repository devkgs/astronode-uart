/**
 * requires libasio-dev from libboost
 */

#include "Transport_layer.h"
#include "Application_layer.h"
/*
 * TODO
 *
 * in application_layer-test, rename expected_ans, because it's not the expected ans but the sent command
 * error codes, two types, error codes from device ans and error codes from transport_layer
 * application_layer.request_cmd should return the transport_layer return value
 * get_answer_error_code, compute error codes and return the right value
 * application_layer, create a method to return the error code from the answer parameters.
 * SimpleSerialFake.h: catch each opcode to return a specific answer
 * SimpleSerial.h: clean code
 * create a fake serial, which can be build to avoid using the hardware for development purpose
 *
 * git sub repo for googletest
 *  * ---general----
 * clang for code formating
 * serial port (win32, termios, (boost))
 * select which serial port driver (win32, termios, boost) to use with cmake
 * port in arguments
 *
 * Improvements:
 * refactor command_t into an object. Move decoding and parsing method into this object.
 */

using namespace std;

#define SERIAL_PORT "/dev/ttyUSB3"

int main(int argc, char* argv[])
{
    if(argc != 2){
        cout << "Missing port as argument" << endl;
        return -1;
    }
    std::cout<<"==================================================="<<std::endl;
    std::shared_ptr<Transport_layer> tr = std::make_shared<Transport_layer>(argv[1]);
    auto cmd = new Command_cfg_r(tr);
    cmd->request_cmd();
    std::cout<<"success: "<<cmd->get_answer_success()<<std::endl;
//   cmd->get_answer_parameters();

    return 0;
}
