/**
 *
 */

#include "Transport_layer.h"
#include "Application_layer.h"

#include <iostream>
#include <future>
#include <thread>
#include <chrono>

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
//   cmd->get_answer_parameters();
    delete cmd;
    return 0;
}
