#ifndef ASTROUART_SERIAL_FAKE_H
#define ASTROUART_SERIAL_FAKE_H

#include <string>
#include <vector>

#include "Serial_interface.h"
#include "Transport_utils.h"

class Serial_fake{//: public Serial{
public:
    Serial_fake(std::string port, unsigned int baud_rate);
    void writeString(std::string s);
     std::vector<uint8_t> readLine();
private:
    std::vector<uint8_t> answer_;
};


#endif //ASTROUART_SERIAL_FAKE_H
