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

TEST(TransportUtilsTest, answer_frame_verification){

}

TEST(TransportUtilsTest, get_success_test){

}

TEST(TransportUtilsTest, get_answer_parameters_test){

}

TEST(TransportUtilsTest, ascii_offset_test){

}

TEST(TransportUtilsTest, hex_offset_test){

}

TEST(TransportUtilsTest, compute_crc_test){

}

TEST(TransportUtilsTest, encode_test){

}
