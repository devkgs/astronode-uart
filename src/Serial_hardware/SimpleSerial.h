/*
 * File:   SimpleSerial.h
 * Author: Terraneo Federico
 * Distributed under the Boost Software License, Version 1.0.
 *
 * Created on September 10, 2009, 12:12 PM
 * @see https://github.com/fedetft/serial-port/blob/master/1_simple/SimpleSerial.h
 */

#ifndef _SIMPLESERIAL_H
#define	_SIMPLESERIAL_H

#include <boost/asio.hpp>
#include <vector>
#include <iostream>

class SimpleSerial
{
public:
    /**
     * Constructor.
     * \param port device name, example "/dev/ttyUSB0" or "COM4"
     * \param baud_rate communication speed, example 9600 or 115200
     * \throws boost::system::system_error if cannot open the
     * serial device
     */
    SimpleSerial(std::string port, unsigned int baud_rate)
            : io(), serial(io,port)
    {
        serial.set_option(boost::asio::serial_port_base::baud_rate(baud_rate));
    }

    /**
     * Write a string to the serial device.
     * \param s string to write
     * \throws boost::system::system_error on failure
     */
    void writeString(std::string s)
    {
        boost::asio::write(serial,boost::asio::buffer(s.c_str(),s.size()));
    }

    /**
     * Blocks until a line is received from the serial device.
     * Eventual '\n' or '\r\n' characters at the end of the string are removed.
     * \return a string containing the received line
     * \throws boost::system::system_error on failure
     */
    std::string _readLine()
    {
        //Reading data char by char, code is optimized for simplicity, not speed
        using namespace boost;
        char c;
        std::string result;
        for(;;)
        {
            asio::read(serial,asio::buffer(&c,1));
            switch(c)
            {
                case '\r':
                    break;
                case 0x02:
                    break;
                case '\n':
                    return result;
                case 0x03:
                    std::cout << "received 0x03" << std::hex << c <<std::endl;
                    return result;
                default:
                    std::cout << "received : " << std::hex << (int)c <<std::endl;
                    result+=c;
            }
        }
    }

    std::vector<uint8_t> readLine()
    {
    //Reading data char by char, code is optimized for simplicity, not speed
    using namespace boost;
    char c;
    std::vector<uint8_t> result;
    std::cout<<"received (hex): ";
    for(;;)
    {

        asio::read(serial,asio::buffer(&c,1));
        std::cout<<std::hex<<(int)c;
        switch(c)
        {
            case '\r':
                break;
            case 0x02:
                break;
            case '\n':
                return result;
            case 0x03:
                return result;
            default:
                result.push_back(c);
        }
        std::cout<<std::endl;
    }
}

private:
    boost::asio::io_service io;
    boost::asio::serial_port serial;
};

#endif	/* _SIMPLESERIAL_H */

