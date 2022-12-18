#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "Transport_layer.h"
#include "Transport_utils.h"
#include "Serial_fake/Serial_fake.h"

using ::testing::Return;

class MockSerial : public Serial_fake{
public:
    MockSerial(std::string port, unsigned int baud_rate) : Serial_fake("portname", 1) {}
    MOCK_METHOD(void, writeString, (std::string port), ());
    MOCK_METHOD(std::vector<uint8_t>, readLine, (), ());
    //MockTransport(std::string port) : Transport_layer(port) {}
    //MOCK_METHOD(Transport_layer::answer_t, request_command, (const std::vector<uint8_t> command), ());
    //MOCK_METHOD(std::vector<uint8_t>, get_answer_parameters, (), ());
};

TEST(TransportTest, request_serial_test)
{
    std::vector<uint8_t> command = {0x02,0x30,0x35,0x30,0x33,0x30,0x30,0x30,0x33,0x42,0x36,0x35,0x31,0x03}; // CFG_W command
    std::vector<uint8_t> ans_param;
    std::vector<uint8_t> expected_ans = {1, 2, 3, 4, 5, 6, 7, 8};
    Transport_layer tr("fake_port");
    MockSerial serial("fake_port", 0);

    EXPECT_CALL(serial , readLine()).Times(1).WillOnce(Return(expected_ans));
    EXPECT_CALL(serial, writeString(std::string(command.begin(), command.end()))).Times(1);
    Transport_layer::serial_port_error_code_t err = tr.request_serial(&serial, command, &ans_param);
    ASSERT_EQ(Transport_layer::serial_port_error_code_t::NO_ERROR, err);
    ASSERT_EQ(expected_ans, ans_param);
}


