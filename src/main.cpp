/**
 * requires libasio-dev from libboost
 */

#include "Transport_layer.h"
#include "Application_layer.h"
/*
 * TODO
 *
 * application_layer, create a method to return the error code from the answer parameters.
 * SimpleSerialFake.h: catch each opcode to return a specific answer
 * SimpleSerial.h: clean code
 *
 * git sub repo for googletest
 *  * ---general----
 * clang for code formating
 * serial port (win32, termios, (boost))
 * select which serial port driver (win32, termios, boost) to use with cmake
 * port in arguments
 *
 * Improvements:
 * refactor Command_t into an object. Move decoding and parsing method into this object.
 */

using namespace std;

#define SERIAL_PORT "/dev/ttyUSB3"

int main(int argc, char* argv[])
{
    if(argc != 2){
        cout << "Missing port as argument" << endl;
        return -1;
    }

    std::shared_ptr<Transport_layer> tr = std::make_shared<Transport_layer>(argv[1]);
    auto cmd = new Command_cfg_r(tr);
    cmd->request_cmd();
    std::cout<<"success: "<<cmd->get_answer_success()<<std::endl;
//   cmd->get_answer_parameters();

    return 0;
}
