#include "Transport.h"
#include <sstream>
#include "SimpleSerial.h"
//#include "SerialInterface.h"
#include <memory>
//#include "SimpleSerialFake.h"
#define COMMAND_CONTENT_MAX_SIZE 1024

// Control bytes
#define AI_START_BYTE 0x02 // The byte which indicates the beginning of a frame.
#define AI_END_BYTE   0x03 // The byte which indicates the end of a frame.

uint8_t Transport::ascii_offset(uint8_t byte) {
    if (byte >= 0x30 && byte <= 0x39) {
        return 48;
    } else if (byte >= 0x41 && byte <= 0x46) {
        return 55;
    }
    return 0;
}

uint8_t Transport::hex_offset(uint8_t byte) {
    if (byte <= 9) {
        return 48;
    } else if (byte >= 0xA && byte <= 0xF) {
        return 55;
    }
    return 0;
}

uint16_t Transport::compute_crc(uint8_t *p_data, uint8_t length) {
    uint16_t x = 0;
    uint16_t crc = 0xFFFF;

    while (length--) {
        x = crc >> 8 ^ *p_data++;
        x ^= x >> 4;
        crc = (crc << 8) ^ (x << 12) ^ (x << 5) ^ (x);
    }
    return crc;
}

std::vector<uint8_t> Transport::encode(std::vector<uint8_t> args) {
    uint8_t data[COMMAND_CONTENT_MAX_SIZE] = {0};
    std::copy(args.begin(), args.end(), data);
    int length = args.size();

    // add crc at the end
    uint16_t crc = Transport::compute_crc(data, args.size());
    data[length++] = (uint8_t) crc;
    data[length++] = (uint8_t) (crc >> 8);

    std::vector<uint8_t> encoded;
    encoded.push_back(AI_START_BYTE);
    for (int i = 0; i < length; i++) {
        uint8_t first_digit = (uint8_t) data[i] >> 4;
        encoded.push_back(first_digit + hex_offset(first_digit));
        uint8_t last_digit = (uint8_t) data[i] & 0xF;
        encoded.push_back(last_digit + hex_offset(last_digit));
    }
    encoded.push_back(AI_END_BYTE);
    return encoded;
}

std::vector<uint8_t> Transport::decode(std::vector<uint8_t> frame) {
    std::vector<uint8_t> decoded;
    for (int i = 0; i < frame.size(); i = i + 2) {
        uint8_t first_digit = (frame.at(i) - ascii_offset(frame.at(i))) << 4;
        uint8_t second_digit = frame.at(i + 1) - ascii_offset(frame.at(i + 1));
        decoded.push_back(first_digit + second_digit);
        //std::cout<<"decode: "<<frame.at(i)<<" "<<frame.at(i+1)<<" "<<std::hex<<first_digit+second_digit<<std::endl;
    }
    return decoded;
}

std::vector<uint8_t> Transport::request_serial(const std::vector<uint8_t> command) {
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

void Transport::request_command(const std::vector<uint8_t> data){
    std::cout<<"sending forced_to_be_override"<<std::endl;
    std::vector<uint8_t> encoded = Transport::encode(data);
    std::vector<uint8_t> answer = Transport::request_serial(encoded);
    decoded_answer_ =  Transport::decode(answer);
}
/* example answer to cfg_r
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

bool Transport::get_answer_success(void){
    return true;
}

std::vector<uint8_t> Transport::get_answer_parameters(void){
    return decoded_answer_;
}


