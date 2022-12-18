#ifndef ASTROUART_SERIAL_FAKE_H
#define ASTROUART_SERIAL_FAKE_H

#include <string>
#include <vector>

#include "Serial_port.h"
#include "Transport_utils.h"


class Serial_fake : public Serial_port {
public:
    Serial_fake(std::string port, unsigned int baud_rate);// : Serial_port(std::string port, unsigned int baud_rate);
    void writeString(std::string s);
    std::vector<uint8_t> readLine();
private:
    std::vector<uint8_t> answer_;
};


#endif //ASTROUART_SERIAL_FAKE_H
