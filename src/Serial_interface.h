#ifndef ASTROUART_SERIAL_INTERFACE_H
#define ASTROUART_SERIAL_INTERFACE_H

#include <vector>

class Serial{
public:
 //   Serial(std::string port, unsigned int baud_rate);
    virtual void writeString(std::string s) = 0;
    virtual std::vector<uint8_t> readLine(void) = 0;
//    virtual ~Serial();
};


#endif //ASTROUART_SERIAL_INTERFACE_H
