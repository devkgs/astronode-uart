#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "Transport_layer.h"
#include "Serial_hardware/SimpleSerial.h"

class MockSerial : public SimpleSerial{
public:
    MockSerial(std::string port, unsigned int baud_rate) : SimpleSerial("portname", 1) {}
    MOCK_METHOD(void, writeString, (std::string port), ());
    MOCK_METHOD(std::vector<uint8_t>, readLine, (), ());
    //MockTransport(std::string port) : Transport_layer(port) {}
    //MOCK_METHOD(Transport_layer::Command_t, request_command, (const std::vector<uint8_t> command), ());
    //MOCK_METHOD(std::vector<uint8_t>, get_answer_parameters, (), ());
};

TEST(TransportTest, request_command_test){
    Transport_layer tr("port");
    std::vector<uint8_t> v;
    tr.request_command(v);
}

TEST(TransportTest, request_serial_port_failure_test){

}

TEST(TransportTest, request_serial_write_failure_test){

}

TEST(TransportTest, request_serial_read_failure_test){

}


