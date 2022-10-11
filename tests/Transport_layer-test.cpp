#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "Transport_layer.h"
#include "Transport_utils.h"
#include "Serial_hardware/SimpleSerial.h"

using ::testing::Return;

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
//    Transport_layer tr("port");
//    std::vector<uint8_t> command = {0x05, 0x03, 0x0, 0x03};
//    Transport_layer::answer_t ans = tr.request_command(command);
}

TEST(TransportTest, request_serial_test){
    Transport_layer tr("fake_port");

    MockSerial serial("fake_port", 0);

    //std::vector<uint8_t> command = {0x02,0x30,0x35,0x30,0x33,0x30,0x30,0x30,0x33,0x42,0x36,0x35,0x31,0x03}; // CFG_W command
    std::vector<uint8_t> command = {0x02,0x31,0x35,0x36,0x34,0x41,0x33,0x03};  // CFG_R command
    std::vector<uint8_t> ans_param;
    std::vector<uint8_t> expected_ans = {1, 2, 3, 4, 5, 6, 7, 8};

    std::vector<uint8_t> ans = tr.request_serial(command, &ans_param);

    std::vector<uint8_t> decoded_answer_ =  Transport_utils::decode(ans);
    // TODO assert param
    ASSERT_EQ(0x95, Transport_utils::get_command_id(decoded_answer_));
    ASSERT_EQ(expected_ans, Transport_utils::get_command_parameters(decoded_answer_));

  //  EXPECT_CALL(s , readLine()).Times(1).WillOnce(Return(expected_ans));

}

