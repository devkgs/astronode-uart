#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "Transport_layer.h"
#include "SimpleSerial.h"

class MockSerial : public SimpleSerial{
public:
    MOCK_METHOD(void, writeString, (std::string), ());
    MOCK_METHOD(std::vector<uint8_t>, readLine, (), ());
    //MOCK_METHOD(void, request_command, (const std::vector<uint8_t> command), ());
    //MOCK_METHOD(bool, get_answer_success, (), ());
    //MOCK_METHOD(std::vector<uint8_t>, get_answer_parameters, (), ());
};


TEST(TransportTest, no_answer_test){

}

TEST(TransportTest, get_answer_success_true_test){

}

TEST(TransportTest, get_answer_success_false_test){

}

TEST(TransportTest, get_answer_parameters_test){

}


