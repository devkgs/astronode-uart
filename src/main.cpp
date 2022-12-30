/**
 *
 */

#include "Transport_layer.h"

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


    return 0;
}
