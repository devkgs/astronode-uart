#ifndef ASTROUART_SERIALINTERFACE_H
#define ASTROUART_SERIALINTERFACE_H

#include <string>
#include <vector>

class SerialInterface {
public:
    SerialInterface(std::string port, unsigned int baud_rate) {}
    virtual ~SerialInterface() { }
    virtual void writeString(std::string s) = 0;
    virtual std::vector<uint8_t> readLine() = 0;
};


#endif //ASTROUART_SERIALINTERFACE_H
