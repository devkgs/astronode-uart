#include "gtest/gtest.h"
//#include "gmock/gmock.h"
#include "Transport_utils.h"


TEST(TransportUtilsTest, decode_test){
    std::vector<uint8_t> frame = {/*0x02, */0x41, 0x36, 0x35, 0x39, 0x30, 0x30, 0x38, 0x37, 0x37, 0x37/*, 0x03*/};  // PLD_DA example
    std::vector<uint8_t> expected_ans = {0xA6, 0x59, 0x00, 0x87, 0x77};
    ASSERT_EQ(expected_ans, Transport_utils::decode(frame));
}

TEST(TransportUtilsTest, get_command_id_test){
    std::vector<uint8_t> frame = {0xA6, 0x59, 0x00, 0x87, 0x77};
    uint8_t expected_ans = 0xA6;
    ASSERT_EQ(expected_ans, Transport_utils::get_command_id(frame));
}

TEST(TransportUtilsTest, get_command_parameters_test){
    std::vector<uint8_t> frame = {0xA6, 0x59, 0x00, 0x87, 0x77};
    std::vector<uint8_t> expected_ans = {0x59, 0x00};
    ASSERT_EQ(expected_ans, Transport_utils::get_command_parameters(frame));
}

TEST(TransportUtilsTest, get_command_crc_test){
    std::vector<uint8_t> frame = {0xA6, 0x59, 0x00, 0x87, 0x77};
    std::vector<uint8_t> expected_ans = {0x87, 0x77};
    ASSERT_EQ(expected_ans, Transport_utils::get_command_crc(frame));
}
/*
TEST(TransportUtilsTest, calculate_crc_test){
    std::vector<uint8_t> param = {0x14, 0x56, 0xF8, 0x9A, 0x00, 0x01};
    uint16_t expected_crc = 0x7FD5;
    ASSERT_EQ(expected_crc, Transport_utils::calculate_crc(param, param.size(), 0xFFFF));

    param = {0x00, 0x00};
    expected_crc = 0x1D0F;
    ASSERT_EQ(expected_crc, Transport_utils::calculate_crc(param, param.size(), 0xFFFF));
}*/

TEST(TransportUtilsTest, compute_crc_test){
    std::vector<uint8_t> frame = {0x26};    // PLD_DR
    uint16_t expected_crc = 0xA554;
    uint8_t data[1024] = {0};
    std::copy(frame.begin(), frame.end(), data);
    ASSERT_EQ(expected_crc, Transport_utils::compute_crc(data, frame.size()));

    frame = {0xA6, 0x59, 0x00};    // PLD_DA
    expected_crc = 0x7787;
    std::copy(frame.begin(), frame.end(), data);
    ASSERT_EQ(expected_crc, Transport_utils::compute_crc(data, frame.size()));
}

TEST(TransportUtilsTest, is_answer_crc_valid_test){
    std::vector<uint8_t> frame = {0x26};    // PLD_DR
    uint16_t expected_crc = 0xA554;
    ASSERT_TRUE(Transport_utils::is_answer_crc_valid(frame, expected_crc));

    frame = {0xA6, 0x59, 0x00};             // PLD_DA
    expected_crc = 0x7787;
    ASSERT_TRUE(Transport_utils::is_answer_crc_valid(frame, expected_crc));

    expected_crc = 0;
    ASSERT_FALSE(Transport_utils::is_answer_crc_valid(frame, expected_crc));
}
