/**
 *
 */

#include "Transport_layer.h"
#include "Application_layer.h"

#include <iostream>
#include <future>
#include <thread>
#include <chrono>
#include <unistd.h>

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
//    auto cmd = new Command_cfg_r(tr);
   // cmd->request_cmd();


//    auto enable_validation_mode_cmd = new Command_val_w(tr);
//    enable_validation_mode_cmd->request_cmd();
//    delete enable_validation_mode_cmd;


//    auto start_auto_tx = new Command_homologation_auto_tx(tr);
//    start_auto_tx->request_cmd();
//    delete start_auto_tx;

//    auto start_duty_cycle_mode = new Command_homologation_start_duty_cycle_mode(tr);
//    start_duty_cycle_mode->request_cmd();
//    delete start_duty_cycle_mode;

//    auto continuous_cmd = new Command_homologation_start_continuous_mode(tr);
//    continuous_cmd->request_cmd();
//    delete continuous_cmd;
//
//    usleep(5*1000*1000);
//
    auto stop_homologation = new Command_homologation_stop_auto_tx(tr);
    stop_homologation->request_cmd();
    delete stop_homologation;

    return 0;
}
