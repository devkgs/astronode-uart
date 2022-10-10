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
    //MOCK_METHOD(Transport_layer::answer_t, request_command, (const std::vector<uint8_t> command), ());
    //MOCK_METHOD(std::vector<uint8_t>, get_answer_parameters, (), ());
};

TEST(TransportTest, request_command_test){
    Transport_layer tr("port");
    std::vector<uint8_t> command = {0x05, 0x03, 0x0, 0x03};
    Transport_layer::answer_t ans = tr.request_command(command);

   // ASSERT_EQ(, ans.error_code);

}

TEST(TransportTest, request_serial_test){

}

