#ifndef ASTROUART_SERIAL_PORT_H
#define ASTROUART_SERIAL_PORT_H


class Serial_port {
public:
   // Serial_port(std::string port, unsigned int baud_rate);
    virtual void writeString(std::string s) = 0;
    //virtual void test(void) = 0;
    virtual std::vector<uint8_t> readLine() = 0;
};


#endif //ASTROUART_SERIAL_PORT_H
