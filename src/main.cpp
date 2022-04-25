/**
 * requires libasio-dev from libboost
 */

#include "Transport_layer.h"
#include "Application_layer.h"
/*
 * TODO
 *
 * Transport_layer.cpp: decode answer, get if error. Return false on error in get_answer_success
 * application_layer, create a method to return the error code from the answer parameters.
 * CmakeList.txt: Different build for fake and real
 * CmakeList.txt: Change name "simple" to a better one
 * RequestCommand-test.cpp: Add arguments in opcodes with arg
 * RequestCommand-test.cpp: Fill remaining empty opcodes
 * SimpleSerialFake.h: catch each opcode to return a specific answer
 * SimpleSerial.h: clean code
 *
 * git sub repo for googletest
 *  * ---general----
 * clang for code formating
 * cmake, select tests to run
 * serial port (win32, termios, (boost))
 * select which serial port driver (win32, termios, boost) to use with cmake
 * port in arguments
 */

/**
 * Architecture:
 * request_command -> serial_commands
 * command ->
 * simpleSerial
 *
 *
 *
 */

using namespace std;

#define SERIAL_PORT "/dev/ttyUSB3"
#define BAUDRATE 9600
int main(int argc, char* argv[])
{
    std::shared_ptr<Transport_layer> tr = std::make_shared<Transport_layer>();
    auto cmd = new Command_cfg_r(tr);
    cmd->request_cmd();
    std::cout<<"success: "<<cmd->get_answer_success()<<std::endl;
//   cmd->get_answer_parameters();

    return 0;
}


//
//void enqueue_dequeue_payload(){
//    int cpt = 0;
//    SimpleSerial serial("/dev/ttyUSB3",9600);
//    // while(1){
//    try {
//        //queue
//        std::string message = {0x02,0x32,0x35,0x65,0x39,0x30,0x33,0x35,0x34,0x36,0x35,0x37,0x33,0x37,0x34,0x44,0x46,0x36,0x37,0x03};
//        //std::cout << "sending queue message: "<<message<<std::endl;
//        std::cout << "sending queue message" << std::endl;
//        for(int i = 0; i< message.size(); i++){
//            std::cout << " 0x" << std::hex << (int) message[i];
//        }
//        std::cout<<std::endl;
//        std::cout<<"message sent, waiting for the answer"<<std::endl;
//        serial.writeString(message);
//        std::string result = serial._readLine();
//        std::cout << result << std::endl;
//        std::cout << "string size : " << dec <<(int)result.size() <<std::endl;
//        for (int i = 0; i < result.size();  i++ ){
//            std::cout << " 0x" << std::hex << (int)result[i];
//        }
//        std::cout << std::endl;
//        if(result.size() != 11){
//            exit(0);
//        }
//        //dequeue
//        message = {0x02,0x32,0x36,0x35,0x34,0x41,0x35,0x03};
//        std::cout << "sending dequeue message: "<<message<<std::endl;
//        //std::cout<<"message sent, waiting for the answer"<<std::endl;
//        std::cout << "sending dequeue message" << std::endl;
//        for(int i = 0; i< message.size(); i++){
//            std::cout << " 0x" << std::hex << (int) message[i];
//        }
//        std::cout<<std::endl;
//        serial.writeString(message);
//        result = serial._readLine();
//        std::cout << result << std::endl;
//        std::cout << "string size : " << dec <<(int)result.size() <<std::endl;
//        for (int i = 0; i < result.size();  i++ ){
//            std::cout << " 0x" << std::hex << (int)result[i];
//        }
//        std::cout << std::endl;
//        if(result.size() != 11){
//            exit(0);
//        }
//        usleep(1000*100);
//    } catch(boost::system::system_error& e)
//    {
//        cout<<"Error: "<<e.what()<<endl;
//    }
//    //  }
//}
//
//
//void offset(void){
///*    std::string st = "Astrocast Mobile6nF0O4Pb6qt0c6TNGR4eWYb4R8fEsXx2h1hGoR6nvku2TvGvTuFzxiGYPpICAAroZKttHnzXTQSLEilvCTT7r7E7urZ7iEW42fdibmXG4ROQz";
//    std::vector<uint8_t> data;
//    std::copy(st.begin(), st.end(), std::back_inserter(data));
//    std::cout<<std::endl;
//    std::vector<uint8_t> encoded = Message::encode(data);
//    for(uint8_t i : encoded){
//        std::cout<<"0x"<<std::hex<<int(i)<<",";
//    }
//    std::cout<<std::endl;
//*/
////std::vector<uint8_t> v = {0x06,0x41,0x73,0x74,0x72,0x6F,0x63,0x61,0x73,0x74,0x20,0x4D,0x6F,0x62,0x69,0x6C,0x65,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x36,0x6E,0x46,0x30,0x4F,0x34,0x50,0x62,0x36,0x71,0x74,0x30,0x63,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x36,0x54,0x4E,0x47,0x52,0x34,0x65,0x57,0x59,0x62,0x34,0x52,0x38,0x66,0x45,0x73,0x58,0x78,0x32,0x68,0x31,0x68,0x47,0x6F,0x52,0x36,0x6E,0x76,0x6B,0x75,0x32,0x54,0x76,0x47,0x76,0x54,0x75,0x46,0x7A,0x78,0x69,0x47,0x59,0x50,0x70,0x49,0x43,0x41,0x41,0x72,0x6F,0x5A,0x4B,0x74,0x74,0x48,0x6E,0x7A,0x58,0x54,0x51,0x53,0x4C,0x45,0x69,0x6C,0x76,0x43,0x54,0x54,0x37,0x72,0x37,0x45,0x37,0x75,0x72,0x5A,0x37,0x69,0x45,0x57,0x34,0x32,0x66,0x64,0x69,0x62,0x6D,0x58,0x47,0x34,0x52,0x4F,0x51,0x7A,0x00,0x65,0x07};
//    std::vector<uint8_t> v = {0x06,0x41,0x73,0x74,0x72,0x6F,0x63,0x61,0x73,0x74,0x20,0x4D,0x6F,0x62,0x69,0x6C,0x65,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x36,0x6E,0x46,0x30,0x4F,0x34,0x50,0x62,0x36,0x71,0x74,0x30,0x63,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x36,0x54,0x4E,0x47,0x52,0x34,0x65,0x57,0x59,0x62,0x34,0x52,0x38,0x66,0x45,0x73,0x58,0x78,0x32,0x68,0x31,0x68,0x47,0x6F,0x52,0x36,0x6E,0x76,0x6B,0x75,0x32,0x54,0x76,0x47,0x76,0x54,0x75,0x46,0x7A,0x78,0x69,0x47,0x59,0x50,0x70,0x49,0x43,0x41,0x41,0x72,0x6F,0x5A,0x4B,0x74,0x74,0x48,0x6E,0x7A,0x58,0x54,0x51,0x53,0x4C,0x45,0x69,0x6C,0x76,0x43,0x54,0x54,0x37,0x72,0x37,0x45,0x37,0x75,0x72,0x5A,0x37,0x69,0x45,0x57,0x34,0x32,0x66,0x64,0x69,0x62,0x6D,0x58,0x47,0x34,0x52,0x4F,0x51};
//    std::vector<uint8_t> encoded = Message::encode(v);
//    for(uint8_t i:encoded){
//        std::cout<<"0x"<<std::hex<<int(i)<<",";
//    }
//    std::cout<<"done"<<std::endl;
//}
//
//
//
//void send_dummy(void){
//    std::cout<<"<<<<<sending dummy char>>>>"<<std::endl;
//    try{
//        SimpleSerial serial("/dev/ttyUSB3",9600);
//        std::string message = { 0x55 };
//        for(int i = 0; i< message.size(); i++){
//            std::cout << " 0x" << std::hex << (int) message[i];
//        }
//        std::cout<<std::endl;
//        std::cout<<"Dummy char sent "<<std::endl;
//        serial.writeString(message);
//
//
//    } catch(boost::system::system_error& e)
//    {
//        cout<<"Error: "<<e.what()<<endl;
//    }
////     usleep(1000*1);
//}
//
//
//int send_once(void){
//    try{
//        SimpleSerial serial("/dev/ttyUSB3",9600);
//        std::string message = {0x02, 0x31, 0x35, 0x36, 0x34, 0x41, 0x33, 0x03};
////        std::string message = { 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78};
//        std::cout << "sending: "<<message<<std::endl;
//        for(int i = 0; i< message.size(); i++){
//            std::cout << " 0x" << std::hex << (int) message[i];
//        }
//        std::cout<<std::endl;
//        std::cout<<"message sent, waiting for the answer"<<std::endl;
//
//        serial.writeString(message);
//
//        std::string result = serial._readLine();
//        std::cout << result << std::endl;
//        std::cout << "string size : " << std::dec << result.size() <<std::endl;
//
//        std::string expected_answer = {0x2, 0x39, 0x35, 0x30, 0x34, 0x30, 0x31, 0x30, 0x32, 0x30, 0x34, 0x30 ,0x30, 0x31, 0x32, 0x30, 0x30, 0x43, 0x44, 0x35, 0x41, 0x31, 0x33};
//        if(result.compare(expected_answer) != 0){
//            std::cout<<"WRONG ANSWER"<<std::endl;
//        }
//        for (int i = 0; i < result.size();  i++ ){
//            std::cout  << " 0x" << std::hex << (int)result[i];
//        }
//        std::cout << std::endl;
//
//    } catch(boost::system::system_error& e)
//    {
//        cout<<"Error: "<<e.what()<<endl;
//        return 1;
//    }
//    return 0;
//}
//
//void send_continuous(void){
//    int cpt = 0;
//    SimpleSerial serial("/dev/ttyUSB3",9600);
//    while(1){
//        try {
//            std::string message = { 0x02, 0x31, 0x35, 0x36, 0x34, (char)0x41, 0x33, 0x03};
//
//            std::cout << "counter= "<<std::dec<<cpt++<<" sending: "<<message<<std::endl;
//            std::cout<<"message sent, waiting for the answer"<<std::endl;
//
//            serial.writeString(message);
//
//            std::string result = serial._readLine();
//            std::cout << result << std::endl;
//            std::cout << "string size : " << result.size() <<std::endl;
//
//            for (int i = 0; i < result.size();  i++ ){
//                std::cout << " 0x" << std::hex << (int)result[i];
//            }
//            std::string expected_answer = {0x2, 0x39, 0x35, 0x30, 0x34, 0x30, 0x31, 0x30, 0x32, 0x30, 0x34, 0x30 ,0x30, 0x31, 0x32, 0x30, 0x30, 0x43, 0x44, 0x35, 0x41, 0x31, 0x33};
//            if(result.compare(expected_answer) != 0){
//                std::cout<<"WRONG ANSWER"<<std::endl;
//                exit(0);
//            }
//            std::cout<<std::endl;
//            usleep(1000*10);
//        } catch(boost::system::system_error& e)
//        {
//            cout<<"Error: "<<e.what()<<endl;
//        }
//    }
//}
//
//void send_wifi_ssid_continuous(void){
//    int cpt = 0;
//    SimpleSerial serial("/dev/ttyUSB3",9600);
//    while(1){
//        try {
//            std::string message = { 0x02,0x30,0x36,0x34,0x31,0x37,0x33,0x37,0x34,0x37,0x32,0x36,0x46,0x36,0x33,0x36,0x31,0x37,0x33,0x37,0x34,0x32,0x30,0x34,0x44,0x36,
//                                    0x46,0x36,0x32,0x36,0x39,0x36,0x43,0x36,0x35,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,
//                                    0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x33,0x36,0x36,0x45,0x34,0x36,0x33,0x30,0x34,
//                                    0x46,0x33,0x34,0x35,0x30,0x36,0x32,0x33,0x36,0x37,0x31,0x37,0x34,0x33,0x30,0x36,0x33,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,
//                                    0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,
//                                    0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,
//                                    0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,
//                                    0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x33,0x36,0x35,0x34,0x34,0x45,0x34,0x37,0x35,0x32,0x33,
//                                    0x34,0x36,0x35,0x35,0x37,0x35,0x39,0x36,0x32,0x33,0x34,0x35,0x32,0x33,0x38,0x36,0x36,0x34,0x35,0x37,0x33,0x35,0x38,0x37,0x38,0x33,
//                                    0x32,0x36,0x38,0x33,0x31,0x36,0x38,0x34,0x37,0x36,0x46,0x35,0x32,0x33,0x36,0x36,0x45,0x37,0x36,0x36,0x42,0x37,0x35,0x33,0x32,0x35,
//                                    0x34,0x37,0x36,0x34,0x37,0x37,0x36,0x35,0x34,0x37,0x35,0x34,0x36,0x37,0x41,0x37,0x38,0x36,0x39,0x34,0x37,0x35,0x39,0x35,0x30,0x37,
//                                    0x30,0x34,0x39,0x34,0x33,0x34,0x31,0x34,0x31,0x37,0x32,0x36,0x46,0x35,0x41,0x34,0x42,0x37,0x34,0x37,0x34,0x34,0x38,0x36,0x45,0x37,
//                                    0x41,0x35,0x38,0x35,0x34,0x35,0x31,0x35,0x33,0x34,0x43,0x34,0x35,0x36,0x39,0x36,0x43,0x37,0x36,0x34,0x33,0x35,0x34,0x35,0x34,0x33,
//                                    0x37,0x37,0x32,0x33,0x37,0x34,0x35,0x33,0x37,0x37,0x35,0x37,0x32,0x35,0x41,0x33,0x37,0x36,0x39,0x34,0x35,0x35,0x37,0x33,0x34,0x33,
//                                    0x32,0x36,0x36,0x36,0x34,0x36,0x39,0x36,0x32,0x36,0x44,0x35,0x38,0x34,0x37,0x33,0x34,0x35,0x32,0x34,0x46,0x35,0x31,0x32,0x43,0x44,
//                                    0x46,0x03};
//
//            std::cout<<"message size = "<<message.size()<<std::endl;
//            std::cout << "counter= "<<std::dec<<cpt++<<" sending: "<<message<<std::endl;
//            std::cout<<"message sent, waiting for the answer"<<std::endl;
//
//            serial.writeString(message);
//
//            std::string result = serial._readLine();
//            std::cout << result << std::endl;
//            std::cout << "string size : " << result.size() <<std::endl;
//
//            for (int i = 0; i < result.size();  i++ ){
//                std::cout << " 0x" << std::hex << (int)result[i];
//            }
//            std::cout<<std::endl;
//            std::string expected_answer = {0x2, 0x46, 0x46, 0x30, 0x31, 0x30, 0x30, 0x43, 0x45, 0x33, 0x30};
//            if(result.compare(expected_answer) != 0){
//                std::cout<<"WRONG ANSWER"<<std::endl;
//                exit(0);
//            }
//            std::cout<<std::endl;
//            usleep(1000*10);
//        } catch(boost::system::system_error& e)
//        {
//            cout<<"Error: "<<e.what()<<endl;
//        }
//        break;
//    }
//}
//
//void noAns_once(void){
//    try {
//
//        SimpleSerial serial("/dev/ttyUSB3",9600);
//
//        std::string message = { 0x02, 0x31, 0x35, 0x36, 0x34, 0x41, 0x33, 0x03};
//        //    std::string message = { 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78};
//        std::cout << "sending: "<<message<<std::endl;
//        std::cout<<"message sent, waiting for the answer"<<std::endl;
//
//        serial.writeString(message);
//
//    } catch(boost::system::system_error& e)
//    {
//        cout<<"Error: "<<e.what()<<endl;
//    }
//}
//
//void noAns_continuous(void){
//    SimpleSerial serial("/dev/ttyUSB3",9600);
//    while(1){
//        try {
//            std::string message = { 0x02, 0x31, 0x35, 0x36, 0x34, 0x41, 0x33, 0x03};
//            //    std::string message = { 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78};
//            std::cout << "sending: "<<message<<std::endl;
//            std::cout<<"message sent, waiting for the answer"<<std::endl;
//            serial.writeString(message);
//            usleep(1000*10);
//        } catch(boost::system::system_error& e)
//        {
//            cout<<"Error: "<<e.what()<<endl;
//
//        }
//    }
//}
//
//int wifi_message(void){
//    try{
//        SimpleSerial serial("/dev/ttyUSB3",9600);
//        //send 001 Test
//        std::string message = {0x02,0x32,0x35,0x65,0x39,0x30,0x33,0x35,0x34,0x36,0x35,0x37,0x33,0x37,0x34,0x44,0x46,0x36,0x37,0x03};
//        std::cout << "sending: "<<message<<std::endl;
//        for(int i = 0; i< message.size(); i++){
//            std::cout << " 0x" << std::hex << (int) message[i];
//        }
//        std::cout<<std::endl;
//        std::cout<<"message sent, waiting for the answer"<<std::endl;
//
//        serial.writeString(message);
//
//        std::string result = serial._readLine();
//        std::cout << result << std::endl;
//        std::cout << "string size : " << std::dec << result.size() <<std::endl;
//
//        for (int i = 0; i < result.size();  i++ ){
//            std::cout  << " 0x" << std::hex << (int)result[i];
//        }
//        std::cout << std::endl;
//
//    } catch(boost::system::system_error& e)
//    {
//        cout<<"Error: "<<e.what()<<endl;
//        return 1;
//    }
//    return 0;
//}
//
//int sak_cr(void){
//    try{
//        SimpleSerial serial("/dev/ttyUSB3",9600);
//        //send 001 Test
//        std::string message = {0x02,0x34,0x36,0x32,0x43,0x42,0x32,0x03};
//        std::cout << "sending: "<<message<<std::endl;
//        for(int i = 0; i< message.size(); i++){
//            std::cout << " 0x" << std::hex << (int) message[i];
//        }
//        std::cout<<std::endl;
//        std::cout<<"message sent, waiting for the answer"<<std::endl;
//
//        serial.writeString(message);
//
//        std::string result = serial._readLine();
//        std::cout << result << std::endl;
//        std::cout << "string size : " << std::dec << result.size() <<std::endl;
//
//        for (int i = 0; i < result.size();  i++ ){
//            std::cout  << " 0x" << std::hex << (int)result[i];
//        }
//        std::cout << std::endl;
//
//    } catch(boost::system::system_error& e)
//    {
//        cout<<"Error: "<<e.what()<<endl;
//        return 1;
//    }
//    return 0;
//}
