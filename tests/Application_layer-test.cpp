#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "Application_layer.h"
#include "Transport_layer.h"

using ::testing::Return;
using ::testing::Return;
using ::testing::Exactly;
//using ::testing::AtLeast;
//using ::testing::AtMost;

class MockTransport : public Transport_layer{
public:
    MockTransport(std::string port) : Transport_layer(port) {}
    MOCK_METHOD(Transport_layer::answer_t, request_command, (const std::vector<uint8_t> command), ());
   // MOCK_METHOD(std::vector<uint8_t>, get_answer_parameters, (), ());
};


// Tests for command object

TEST(CommandTest, request_cmd_test){
    std::shared_ptr<MockTransport> tr = std::make_shared<MockTransport>("fake_port");
    auto cmd = new Application_layer(tr);

    std::vector<uint8_t> data = {0};
    EXPECT_CALL(*tr, request_command(data)).Times(Exactly(1));
    cmd->request_cmd(data);

    delete cmd;
}

TEST(CommandTest, get_answer_error_code_test){
    std::shared_ptr<MockTransport> tr = std::make_shared<MockTransport>("fake_port");
    auto cmd = new Application_layer(tr);

    // call request_command first to save locally the result
    Transport_layer::answer_t mock_ans;
    mock_ans.error_code = serial_port_error_code::NO_ERROR;
    mock_ans.answer_id = 0x85;
    mock_ans.answer_parameters = {0};

    std::vector<uint8_t> data = {0x15};

    // request_cmd not called. Return error code ok since there is no way to inform that request was not sent
    ASSERT_EQ(Application_layer::astronode_error_code::ASTRONODE_ERR_CODE_OK, cmd->get_answer_error_code());

    // no error
    EXPECT_CALL(*tr, request_command(data)).Times(1).WillOnce(Return(mock_ans));
    cmd->request_cmd(data);
    ASSERT_EQ(Application_layer::astronode_error_code::ASTRONODE_ERR_CODE_OK, cmd->get_answer_error_code());

    // weird case, answer_id says error, but param says no error
    mock_ans.answer_id = 0xff;
    mock_ans.answer_parameters = {0x0, 0x0};
    EXPECT_CALL(*tr, request_command(data)).Times(1).WillOnce(Return(mock_ans));
    cmd->request_cmd(data);
    ASSERT_EQ(Application_layer::astronode_error_code::ASTRONODE_ERR_CODE_OK, cmd->get_answer_error_code());

    // error code crc not valid
    mock_ans.answer_id = 0xff;
    mock_ans.answer_parameters = {0x0, 0x1};
    EXPECT_CALL(*tr, request_command(data)).Times(1).WillOnce(Return(mock_ans));
    cmd->request_cmd(data);
    ASSERT_EQ(Application_layer::astronode_error_code::ASTRONODE_ERR_CODE_CRC_NOT_VALID, cmd->get_answer_error_code());

    // not all error codes are tested

    // error code no clear
    mock_ans.answer_id = 0xff;
    mock_ans.answer_parameters = {0x46, 0x01};
    EXPECT_CALL(*tr, request_command(data)).Times(1).WillOnce(Return(mock_ans));
    cmd->request_cmd(data);
    ASSERT_EQ(Application_layer::astronode_error_code::ASTRONODE_ERR_CODE_NO_CLEAR, cmd->get_answer_error_code());
}

TEST(CommandTest, get_serial_port_error_code_test){
    std::shared_ptr<MockTransport> tr = std::make_shared<MockTransport>("fake_port");
    auto cmd = new Application_layer(tr);

    // call request_command first to save locally the result
    Transport_layer::answer_t mock_ans;
    mock_ans.error_code = serial_port_error_code_t::NO_ERROR;
    mock_ans.answer_id = 0x95;
    mock_ans.answer_parameters = {0};

    std::vector<uint8_t> data = {0x15};

    // request_cmd not called, return false
    ASSERT_EQ(serial_port_error_code_t::NO_REQUEST_SENT, cmd->get_serial_port_error_code());

    // no error
    EXPECT_CALL(*tr, request_command(data)).Times(1).WillOnce(Return(mock_ans));
    cmd->request_cmd(data);
    ASSERT_EQ(serial_port_error_code_t::NO_ERROR, cmd->get_serial_port_error_code());

    // error
    mock_ans.error_code = serial_port_error_code_t::TIMEOUT_ERROR;
    EXPECT_CALL(*tr, request_command(data)).Times(1).WillOnce(Return(mock_ans));
    cmd->request_cmd(data);
    ASSERT_EQ(serial_port_error_code_t::TIMEOUT_ERROR, cmd->get_serial_port_error_code());
}

TEST(CommandTest, get_answer_parameters_test){
    std::shared_ptr<MockTransport> tr = std::make_shared<MockTransport>("fake_port");

    auto cmd = new Application_layer(tr);

    // call request_command first to save locally the result
    Transport_layer::answer_t mock_ans;
    mock_ans.answer_parameters = {0x12, 0x34};
    std::vector<uint8_t> data = {0x15};
    EXPECT_CALL(*tr, request_command(data)).Times(1).WillOnce(Return(mock_ans));
    cmd->request_cmd(data);

    ASSERT_EQ(mock_ans.answer_parameters, cmd->get_answer_parameters());
    delete cmd;
}


// Tests for commands childs

TEST(CommandTest, cfg_w_test){
    std::shared_ptr<MockTransport> tr = std::make_shared<MockTransport>("fake_port");
    auto cmd = new Command_cfg_w(tr);
    std::vector<uint8_t> data = {0x05, 0x03, 0x0, 0x03};
    EXPECT_CALL(*tr, request_command(data)).Times(1);
    cmd->request_cmd(1, 1, 0, 0, 1, 1);

    delete cmd;
}

TEST(CommandTest, wif_w_test){
    std::shared_ptr<MockTransport> tr = std::make_shared<MockTransport>("fake_port");
    auto cmd = new Command_wif_w(tr);

    uint8_t wlan_ssid[SSID_LENGTH] = {0x6D, 0x79, 0x5F, 0x77, 0x69, 0x66, 0x69, 0x5F, 0x73, 0x73,0x69, 0x64};
    uint8_t wlan_key[PASSWORD_LENGTH] = {0x6D, 0x79, 0x5F, 0x77, 0x69, 0x66, 0x69, 0x5F, 0x70, 0x61,0x73, 0x73, 0x77, 0x6F, 0x72, 0x64};
    uint8_t auth_token[TOKEN_LENGTH] = {0x36, 0x6E, 0x78, 0x47, 0x52, 0x34, 0x65, 0x57, 0x59, 0x62, 0x34, 0x52, 0x38, 0x66, 0x45, 0x73, 0x58, 0x78, 0x32, 0x68, 0x31, 0x68, 0x47, 0x6F, 0x52, 0x36, 0x6E, 0x76, 0x6B, 0x75, 0x32, 0x54, 0x76, 0x47, 0x76, 0x54, 0x75, 0x46, 0x7A, 0x78, 0x69, 0x47, 0x59, 0x50, 0x70, 0x49, 0x43, 0x41, 0x41, 0x72, 0x6F, 0x5A, 0x4B, 0x74, 0x74, 0x48, 0x6E, 0x7A, 0x58, 0x54, 0x51, 0x53, 0x4C, 0x45, 0x69, 0x6C, 0x76, 0x43, 0x54, 0x54, 0x37, 0x72, 0x37, 0x45, 0x37, 0x75, 0x72, 0x5A, 0x37, 0x69, 0x45, 0x57, 0x34, 0x32, 0x66, 0x64, 0x69, 0x62, 0x6D, 0x58, 0x47, 0x34, 0x52, 0x4F, 0x51, 0x7A};

    std::vector<uint8_t> data = {0x06};
    data.insert(data.end(), &wlan_ssid[0], &wlan_ssid[SSID_LENGTH]);
    data.insert(data.end(), &wlan_key[0], &wlan_key[PASSWORD_LENGTH]);
    data.insert(data.end(), &auth_token[0], &auth_token[TOKEN_LENGTH]);

    EXPECT_CALL(*tr, request_command(data)).Times(1);
    cmd->request_cmd("my_wifi_ssid", "my_wifi_password", "6nxGR4eWYb4R8fEsXx2h1hGoR6nvku2TvGvTuFzxiGYPpICAAroZKttHnzXTQSLEilvCTT7r7E7urZ7iEW42fdibmXG4ROQz");

    delete cmd;
}

TEST(CommandTest, ssh_w_test){
    std::shared_ptr<MockTransport> tr = std::make_shared<MockTransport>("fake_port");
    auto cmd = new Command_ssc_w(tr);
    std::vector<uint8_t> data = {0x07, 0x12, 0x1};
    EXPECT_CALL(*tr, request_command(data)).Times(1);
    cmd->request_cmd(0x12, 1);

    data.at(2) = 0x0;
    EXPECT_CALL(*tr, request_command(data)).Times(1);
    cmd->request_cmd(0x12, 0);

    delete cmd;
}

TEST(CommandTest, cfg_s_test){
    std::shared_ptr<MockTransport> tr = std::make_shared<MockTransport>("fake_port");
    auto cmd = new Command_cfg_s(tr);
    std::vector<uint8_t> data = {0x10};
    EXPECT_CALL(*tr, request_command(data)).Times(1);
    cmd->request_cmd();
    delete cmd;
}

TEST(CommandTest, cfg_f_test){
    std::shared_ptr<MockTransport> tr = std::make_shared<MockTransport>("fake_port");
    auto cmd = new Command_cfg_f(tr);
    std::vector<uint8_t> data = {0x11};
    EXPECT_CALL(*tr, request_command(data)).Times(1);
    cmd->request_cmd();
    delete cmd;
}

TEST(CommandTest, cfg_r_test){
    std::shared_ptr<MockTransport> tr = std::make_shared<MockTransport>("fake_port");
    auto cmd = new Command_cfg_r(tr);
    std::vector<uint8_t> data = {0x15};
    Transport_layer::answer_t mock_ans;
    mock_ans.answer_parameters = {0x03, 0x01, 0x02, 0x01, 0x00, 0x05, 0x00, 0x01};

    EXPECT_CALL(*tr, request_command(data)).Times(1).WillOnce(Return(mock_ans));
    cmd->request_cmd();
    ASSERT_EQ(mock_ans.answer_parameters, cmd->get_answer_parameters());

    delete cmd;
}

TEST(CommandTest, cfg_r_get_product_id_test) {
    std::shared_ptr<MockTransport> tr = std::make_shared<MockTransport>("fake_port");
    auto cmd = new Command_cfg_r(tr);
    std::vector<uint8_t> data = {0x15};
    Transport_layer::answer_t mock_ans;
    mock_ans.answer_parameters = {0x03, 0x01, 0x02, 0x01, 0x00, 0x05, 0x00, 0x01};

    EXPECT_CALL(*tr, request_command(data)).Times(1).WillOnce(Return(mock_ans));
    cmd->request_cmd();

    ASSERT_EQ(0x03, cmd->get_product_id());

    delete cmd;
}

TEST(CommandTest, cfg_r_get_hardware_revision_test) {
    std::shared_ptr<MockTransport> tr = std::make_shared<MockTransport>("fake_port");
    auto cmd = new Command_cfg_r(tr);
    std::vector<uint8_t> data = {0x15};
    Transport_layer::answer_t mock_ans;
    mock_ans.answer_parameters = {0x03, 0x01, 0x02, 0x01, 0x00, 0x05, 0x00, 0x01};

    EXPECT_CALL(*tr, request_command(data)).Times(1).WillOnce(Return(mock_ans));
    cmd->request_cmd();

    ASSERT_EQ(0x01, cmd->get_hardware_revision());

    delete cmd;
}

TEST(CommandTest, cfg_r_get_firmware_major_version_test) {
    std::shared_ptr<MockTransport> tr = std::make_shared<MockTransport>("fake_port");
    auto cmd = new Command_cfg_r(tr);
    std::vector<uint8_t> data = {0x15};
    Transport_layer::answer_t mock_ans;
    mock_ans.answer_parameters = {0x03, 0x01, 0x02, 0x01, 0x00, 0x05, 0x00, 0x01};

    EXPECT_CALL(*tr, request_command(data)).Times(1).WillOnce(Return(mock_ans));
    cmd->request_cmd();

    ASSERT_EQ(0x02, cmd->get_firmware_major_version());

    delete cmd;
}

TEST(CommandTest, cfg_r_get_firmware_minor_version_test) {
    std::shared_ptr<MockTransport> tr = std::make_shared<MockTransport>("fake_port");
    auto cmd = new Command_cfg_r(tr);
    std::vector<uint8_t> data = {0x15};
    Transport_layer::answer_t mock_ans;
    mock_ans.answer_parameters = {0x03, 0x01, 0x02, 0x01, 0x00, 0x05, 0x00, 0x01};

    EXPECT_CALL(*tr, request_command(data)).Times(1).WillOnce(Return(mock_ans));
    cmd->request_cmd();

    ASSERT_EQ(0x01, cmd->get_firmware_minor_version());

    delete cmd;
}

TEST(CommandTest, cfg_r_get_firmware_revision_test) {
    std::shared_ptr<MockTransport> tr = std::make_shared<MockTransport>("fake_port");
    auto cmd = new Command_cfg_r(tr);
    std::vector<uint8_t> data = {0x15};
    Transport_layer::answer_t mock_ans;
    mock_ans.answer_parameters = {0x03, 0x01, 0x02, 0x01, 0x00, 0x05, 0x00, 0x01};

    EXPECT_CALL(*tr, request_command(data)).Times(1).WillOnce(Return(mock_ans));
    cmd->request_cmd();

    ASSERT_EQ(0x00, cmd->get_firmware_revision());

    delete cmd;
}

TEST(CommandTest, cfg_r_get_payload_ack_test) {
    std::shared_ptr<MockTransport> tr = std::make_shared<MockTransport>("fake_port");
    auto cmd = new Command_cfg_r(tr);
    std::vector<uint8_t> data = {0x15};
    Transport_layer::answer_t mock_ans;

    // payload ack is true
    mock_ans.answer_parameters = {0x03, 0x01, 0x02, 0x01, 0x00, 0x01, 0x00, 0x01};

    EXPECT_CALL(*tr, request_command(data)).Times(1).WillOnce(Return(mock_ans));
    cmd->request_cmd();

    ASSERT_EQ(true, cmd->get_payload_ack());

    // payload ack is false
    mock_ans.answer_parameters = {0x03, 0x01, 0x02, 0x01, 0x00, 0x00, 0x00, 0x01};

    EXPECT_CALL(*tr, request_command(data)).Times(1).WillOnce(Return(mock_ans));
    cmd->request_cmd();

    ASSERT_EQ(false, cmd->get_payload_ack());

    delete cmd;
}

TEST(CommandTest, cfg_r_get_add_geolocation_test) {
    std::shared_ptr<MockTransport> tr = std::make_shared<MockTransport>("fake_port");
    auto cmd = new Command_cfg_r(tr);
    std::vector<uint8_t> data = {0x15};
    Transport_layer::answer_t mock_ans;

    // add geolocation is true
    mock_ans.answer_parameters = {0x03, 0x01, 0x02, 0x01, 0x00, 0x02, 0x00, 0x01};

    EXPECT_CALL(*tr, request_command(data)).Times(1).WillOnce(Return(mock_ans));
    cmd->request_cmd();

    ASSERT_EQ(true, cmd->get_add_geolocation());

    // add geolocation is false
    mock_ans.answer_parameters = {0x03, 0x01, 0x02, 0x01, 0x00, 0x00, 0x00, 0x01};

    EXPECT_CALL(*tr, request_command(data)).Times(1).WillOnce(Return(mock_ans));
    cmd->request_cmd();

    ASSERT_EQ(false, cmd->get_add_geolocation());

    delete cmd;
}

TEST(CommandTest, cfg_r_get_ephemeris_enabled_test) {
    std::shared_ptr<MockTransport> tr = std::make_shared<MockTransport>("fake_port");
    auto cmd = new Command_cfg_r(tr);
    std::vector<uint8_t> data = {0x15};
    Transport_layer::answer_t mock_ans;

    // ephemeris enabled is true
    mock_ans.answer_parameters = {0x03, 0x01, 0x02, 0x01, 0x00, 0x04, 0x00, 0x01};

    EXPECT_CALL(*tr, request_command(data)).Times(1).WillOnce(Return(mock_ans));
    cmd->request_cmd();

    ASSERT_EQ(true, cmd->get_ephemeris_enabled());

    // ephemeris enabled is false
    mock_ans.answer_parameters = {0x03, 0x01, 0x02, 0x01, 0x00, 0x00, 0x00, 0x01};

    EXPECT_CALL(*tr, request_command(data)).Times(1).WillOnce(Return(mock_ans));
    cmd->request_cmd();

    ASSERT_EQ(false, cmd->get_ephemeris_enabled());

    delete cmd;
}

TEST(CommandTest, cfg_r_get_deep_sleep_enabled_test) {
    std::shared_ptr<MockTransport> tr = std::make_shared<MockTransport>("fake_port");
    auto cmd = new Command_cfg_r(tr);
    std::vector<uint8_t> data = {0x15};
    Transport_layer::answer_t mock_ans;

    // deep sleep enabled is true
    mock_ans.answer_parameters = {0x03, 0x01, 0x02, 0x01, 0x00, 0x08, 0x00, 0x01};

    EXPECT_CALL(*tr, request_command(data)).Times(1).WillOnce(Return(mock_ans));
    cmd->request_cmd();

    ASSERT_EQ(true, cmd->get_deep_sleep_enabled());

    // deep sleep enabled is false
    mock_ans.answer_parameters = {0x03, 0x01, 0x02, 0x01, 0x00, 0x00, 0x00, 0x01};

    EXPECT_CALL(*tr, request_command(data)).Times(1).WillOnce(Return(mock_ans));
    cmd->request_cmd();

    ASSERT_EQ(false, cmd->get_deep_sleep_enabled());

    delete cmd;
}

TEST(CommandTest, cfg_r_get_payload_ack_evt_pin_enabled_test) {
    std::shared_ptr<MockTransport> tr = std::make_shared<MockTransport>("fake_port");
    auto cmd = new Command_cfg_r(tr);
    std::vector<uint8_t> data = {0x15};
    Transport_layer::answer_t mock_ans;

    // payload ack evt pin enabled is true
    mock_ans.answer_parameters = {0x03, 0x01, 0x02, 0x01, 0x00, 0x08, 0x00, 0x01};

    EXPECT_CALL(*tr, request_command(data)).Times(1).WillOnce(Return(mock_ans));
    cmd->request_cmd();

    ASSERT_EQ(true, cmd->get_payload_ack_evt_pin_enabled());

    // payload ack evt pin enabled is false
    mock_ans.answer_parameters = {0x03, 0x01, 0x02, 0x01, 0x00, 0x00, 0x00, 0x00};

    EXPECT_CALL(*tr, request_command(data)).Times(1).WillOnce(Return(mock_ans));
    cmd->request_cmd();

    ASSERT_EQ(false, cmd->get_payload_ack_evt_pin_enabled());

    delete cmd;
}

TEST(CommandTest, cfg_r_get_reset_notification_evt_pin_enabled_test) {
    std::shared_ptr<MockTransport> tr = std::make_shared<MockTransport>("fake_port");
    auto cmd = new Command_cfg_r(tr);
    std::vector<uint8_t> data = {0x15};
    Transport_layer::answer_t mock_ans;

    // reset notification evt pin enabled is true
    mock_ans.answer_parameters = {0x03, 0x01, 0x02, 0x01, 0x00, 0x08, 0x00, 0x02};

    EXPECT_CALL(*tr, request_command(data)).Times(1).WillOnce(Return(mock_ans));
    cmd->request_cmd();

    ASSERT_EQ(true, cmd->get_reset_notification_evt_pin_enabled());

    // reset notification evt pin enabled is false
    mock_ans.answer_parameters = {0x03, 0x01, 0x02, 0x01, 0x00, 0x00, 0x00, 0x00};

    EXPECT_CALL(*tr, request_command(data)).Times(1).WillOnce(Return(mock_ans));
    cmd->request_cmd();

    ASSERT_EQ(false, cmd->get_reset_notification_evt_pin_enabled());

    delete cmd;
}

TEST(CommandTest, cfg_r_get_command_available_evt_pin_enabled_test) {
    std::shared_ptr<MockTransport> tr = std::make_shared<MockTransport>("fake_port");
    auto cmd = new Command_cfg_r(tr);
    std::vector<uint8_t> data = {0x15};
    Transport_layer::answer_t mock_ans;

    // command available evt pin enabled is true
    mock_ans.answer_parameters = {0x03, 0x01, 0x02, 0x01, 0x00, 0x08, 0x00, 0x04};

    EXPECT_CALL(*tr, request_command(data)).Times(1).WillOnce(Return(mock_ans));
    cmd->request_cmd();

    ASSERT_EQ(true, cmd->get_command_available_evt_pin_enabled());

    // command available evt pin enabled is false
    mock_ans.answer_parameters = {0x03, 0x01, 0x02, 0x01, 0x00, 0x00, 0x00, 0x00};

    EXPECT_CALL(*tr, request_command(data)).Times(1).WillOnce(Return(mock_ans));
    cmd->request_cmd();

    ASSERT_EQ(false, cmd->get_command_available_evt_pin_enabled());

    delete cmd;
}

TEST(CommandTest, cfg_r_get_message_transmission_pending_evt_pin_enabled_test) {
    std::shared_ptr<MockTransport> tr = std::make_shared<MockTransport>("fake_port");
    auto cmd = new Command_cfg_r(tr);
    std::vector<uint8_t> data = {0x15};
    Transport_layer::answer_t mock_ans;

    // message transmission pending evt pin enabled is true
    mock_ans.answer_parameters = {0x03, 0x01, 0x02, 0x01, 0x00, 0x08, 0x00, 0x08};

    EXPECT_CALL(*tr, request_command(data)).Times(1).WillOnce(Return(mock_ans));
    cmd->request_cmd();

    ASSERT_EQ(true, cmd->get_message_transmission_pending_evt_pin_enabled());

    // message transmission pending evt pin enabled is false
    mock_ans.answer_parameters = {0x03, 0x01, 0x02, 0x01, 0x00, 0x00, 0x00, 0x00};

    EXPECT_CALL(*tr, request_command(data)).Times(1).WillOnce(Return(mock_ans));
    cmd->request_cmd();

    ASSERT_EQ(false, cmd->get_message_transmission_pending_evt_pin_enabled());

    delete cmd;
}


TEST(CommandTest, rtc_r_test){
    std::shared_ptr<MockTransport> tr = std::make_shared<MockTransport>("fake_port");
    auto cmd = new Command_rtc_r(tr);
    std::vector<uint8_t> data = {0x17};
    Transport_layer::answer_t mock_ans;
    mock_ans.answer_parameters = {0x12, 0x34, 0x56, 0x78};
    EXPECT_CALL(*tr, request_command(data)).Times(1).WillOnce(Return(mock_ans));
    cmd->request_cmd();

    ASSERT_EQ(mock_ans.answer_parameters, cmd->get_answer_parameters());

    // TODO add get_rtc_time method test

    delete cmd;
}

TEST(CommandTest, nco_r_test){
    std::shared_ptr<MockTransport> tr = std::make_shared<MockTransport>("fake_port");
    auto cmd = new Command_nco_r(tr);
    std::vector<uint8_t> data = {0x18};
    Transport_layer::answer_t mock_ans;
    mock_ans.answer_parameters = {0x12, 0x34, 0x56, 0x78};
    EXPECT_CALL(*tr, request_command(data)).Times(1).WillOnce(Return(mock_ans));
    cmd->request_cmd();

    ASSERT_EQ(mock_ans.answer_parameters, cmd->get_answer_parameters());

    // TODO add get_time_to_next_pass method test

    delete cmd;
}

TEST(CommandTest, mgi_r_test){
    std::shared_ptr<MockTransport> tr = std::make_shared<MockTransport>("fake_port");
    auto cmd = new Command_mgi_r(tr);
    std::vector<uint8_t> data = {0x19};
    Transport_layer::answer_t expected_ans;
    expected_ans.answer_parameters = {0x36};   //don't care about the content
    EXPECT_CALL(*tr, request_command(data)).Times(1).WillOnce(Return(expected_ans));
    cmd->request_cmd();

    ASSERT_EQ(expected_ans.answer_parameters, cmd->get_answer_parameters());

    delete cmd;
}

TEST(CommandTest, msn_r_test){
    std::shared_ptr<MockTransport> tr = std::make_shared<MockTransport>("fake_port");
    auto cmd = new Command_msn_r(tr);
    std::vector<uint8_t> data = {0x1A};
    Transport_layer::answer_t expected_ans;
    expected_ans.answer_parameters = {0x36};   //don't care about the content
    EXPECT_CALL(*tr, request_command(data)).Times(1).WillOnce(Return(expected_ans));
    cmd->request_cmd();

    ASSERT_EQ(expected_ans.answer_parameters, cmd->get_answer_parameters());

    delete cmd;
}

TEST(CommandTest, mpn_r_test){
    std::shared_ptr<MockTransport> tr = std::make_shared<MockTransport>("fake_port");
    auto cmd = new Command_mpn_r(tr);
    std::vector<uint8_t> data = {0x1B};
    Transport_layer::answer_t expected_ans;
    expected_ans.answer_parameters = {0x36};   //don't care about the content
    EXPECT_CALL(*tr, request_command(data)).Times(1).WillOnce(Return(expected_ans));
    cmd->request_cmd();

    ASSERT_EQ(expected_ans.answer_parameters, cmd->get_answer_parameters());

    delete cmd;
}

TEST(CommandTest, pld_e_test){
    std::shared_ptr<MockTransport> tr = std::make_shared<MockTransport>("fake_port");
    auto cmd = new Command_pld_e(tr);
    std::vector<uint8_t> data = {0x03, 0xE9, 0x54, 0x65, 0x73, 0x74};
    std::vector<uint8_t> data_with_id = data;
    data_with_id.insert(data_with_id.begin(), 0x25);

    Transport_layer::answer_t expected_ans;
    expected_ans.answer_parameters = {0x03, 0xE9};
    EXPECT_CALL(*tr, request_command(data_with_id)).Times(1).WillOnce(Return(expected_ans));
    cmd->request_cmd(1001, "Test");

    //Test answer value
    ASSERT_EQ(expected_ans.answer_parameters, cmd->get_answer_parameters());

    // Test get_command_id, convert hex value vector to uint16
    std::vector<uint8_t> command_id_ans = {0x03, 0xE9};
    ASSERT_EQ(1001, cmd->get_command_id());

    delete cmd;
}

TEST(CommandTest, pld_d_test){
    std::shared_ptr<MockTransport> tr = std::make_shared<MockTransport>("fake_port");
    auto cmd = new Command_pld_d(tr);
    std::vector<uint8_t> data = {0x26};
    Transport_layer::answer_t command_id_ans;
    command_id_ans.answer_parameters = {0x03, 0xE9};
    EXPECT_CALL(*tr, request_command(data)).Times(1).WillOnce(Return(command_id_ans));
    cmd->request_cmd();

    // Test get_command_id, convert hex value vector to uint16
    ASSERT_EQ(1001, cmd->get_command_id());

    delete cmd;
}

TEST(CommandTest, pld_f_test){
    std::shared_ptr<MockTransport> tr = std::make_shared<MockTransport>("fake_port");
    auto cmd = new Command_pld_f(tr);
    std::vector<uint8_t> data = {0x27};
    EXPECT_CALL(*tr, request_command(data)).Times(1);
    cmd->request_cmd();

    delete cmd;
}

TEST(CommandTest, geo_w_test){
    std::shared_ptr<MockTransport> tr = std::make_shared<MockTransport>("fake_port");
    auto cmd = new Command_geo_w(tr);
    // TODO add geo write test
    delete cmd;
}

TEST(CommandTest, evt_r_test){
    std::shared_ptr<MockTransport> tr = std::make_shared<MockTransport>("fake_port");
    auto cmd = new Command_evt_r(tr);
    std::vector<uint8_t> data = {0x65};
    EXPECT_CALL(*tr, request_command(data)).Times(1);
    cmd->request_cmd();

    // get parameters test
    Transport_layer::answer_t expected_ans;
    expected_ans.answer_parameters = {0xf};

    EXPECT_CALL(*tr, request_command(data)).Times(1).WillOnce(Return(expected_ans));
    cmd->request_cmd();
    ASSERT_EQ(expected_ans.answer_parameters, cmd->get_answer_parameters());

    expected_ans.answer_parameters  = {0x0};
    EXPECT_CALL(*tr, request_command(data)).Times(1).WillOnce(Return(expected_ans));
    cmd->request_cmd();
    ASSERT_EQ(expected_ans.answer_parameters, cmd->get_answer_parameters());

    // get sak available answer
    expected_ans.answer_parameters = {0x1};
    EXPECT_CALL(*tr, request_command(data)).Times(1).WillOnce(Return(expected_ans));
    cmd->request_cmd();
    ASSERT_EQ(1, cmd->get_sak_available());

    expected_ans.answer_parameters = {0x0};
    EXPECT_CALL(*tr, request_command(data)).Times(1).WillOnce(Return(expected_ans));
    cmd->request_cmd();
    ASSERT_EQ(0, cmd->get_sak_available());

    // get module reset answer
    expected_ans.answer_parameters = {0x2};
    EXPECT_CALL(*tr, request_command(data)).Times(1).WillOnce(Return(expected_ans));
    cmd->request_cmd();
    ASSERT_EQ(1, cmd->get_module_reset());

    expected_ans.answer_parameters = {0x0};
    EXPECT_CALL(*tr, request_command(data)).Times(1).WillOnce(Return(expected_ans));
    cmd->request_cmd();
    ASSERT_EQ(0, cmd->get_module_reset());

    // get command available answer
    expected_ans.answer_parameters = {0x4};
    EXPECT_CALL(*tr, request_command(data)).Times(1).WillOnce(Return(expected_ans));
    cmd->request_cmd();
    ASSERT_EQ(1, cmd->get_command_available());

    expected_ans.answer_parameters = {0x0};
    EXPECT_CALL(*tr, request_command(data)).Times(1).WillOnce(Return(expected_ans));
    cmd->request_cmd();
    ASSERT_EQ(0, cmd->get_command_available());

    // get message transmit pending answer
    expected_ans.answer_parameters = {0x8};
    EXPECT_CALL(*tr, request_command(data)).Times(1).WillOnce(Return(expected_ans));
    cmd->request_cmd();
    ASSERT_EQ(1, cmd->get_message_transmit_pending());

    expected_ans.answer_parameters = {0x0};
    EXPECT_CALL(*tr, request_command(data)).Times(1).WillOnce(Return(expected_ans));
    cmd->request_cmd();
    ASSERT_EQ(0, cmd->get_message_transmit_pending());

    delete cmd;
}

TEST(CommandTest, sak_r_test){
    std::shared_ptr<MockTransport> tr = std::make_shared<MockTransport>("fake_port");
    auto cmd = new Command_sak_r(tr);
    std::vector<uint8_t> data = {0x45};
    Transport_layer::answer_t command_id_ans;
    command_id_ans.answer_parameters = {0x03, 0xE9};
    EXPECT_CALL(*tr, request_command(data)).Times(1).WillOnce(Return(command_id_ans));
    cmd->request_cmd();

    // Test get_command_id, convert hex value vector to uint16
    ASSERT_EQ(1001, cmd->get_command_id());

    delete cmd;
}

TEST(CommandTest, sak_c_test){
    std::shared_ptr<MockTransport> tr = std::make_shared<MockTransport>("fake_port");
    auto cmd = new Command_sak_c(tr);
    std::vector<uint8_t> data = {0x46};
    EXPECT_CALL(*tr, request_command(data)).Times(1);
    cmd->request_cmd();

    delete cmd;
}

TEST(CommandTest, cmd_r_test){
    std::shared_ptr<MockTransport> tr = std::make_shared<MockTransport>("fake_port");
    auto cmd = new Command_cmd_r(tr);
  /*  std::vector<uint8_t> data = {0x47};
    std::vector<uint8_t> payload_8bytes = {0x48, 0x65 ,0x6C, 0x6C, 0x6F, 0x31, 0x32, 0x33, 0x34};

    Transport_layer::answer_t command_id_ans;
    command_id_ans.answer_parameters = {0x03, 0xE9};

    std::vector<uint8_t> expected_ans = {0x03, 0xC2, 0x67, 0x00};
    expected_ans.insert(expected_ans.end(), payload_8bytes.begin(), payload_8bytes.end());
    EXPECT_CALL(*tr, request_command(data)).Times(1).WillOnce(Return(expected_ans));
    cmd->request_cmd();

    // test created date answer
    ASSERT_EQ(63072000, cmd->get_created_date());

    // test payload answer ( 8 and 40 char)
    ASSERT_EQ(payload_8bytes, cmd->get_payload());
    // TODO add test for 40bytes payload
*/
    delete cmd;
}

TEST(CommandTest, cmd_c_test){
    std::shared_ptr<MockTransport> tr = std::make_shared<MockTransport>("fake_port");
    auto cmd = new Command_cmd_c(tr);
    std::vector<uint8_t> data = {0x48};
    EXPECT_CALL(*tr, request_command(data)).Times(1);
    cmd->request_cmd();

    delete cmd;
}

TEST(CommandTest, res_c_test){
    std::shared_ptr<MockTransport> tr = std::make_shared<MockTransport>("fake_port");
    auto cmd = new Command_res_c(tr);
    std::vector<uint8_t> data = {0x55};
    EXPECT_CALL(*tr, request_command(data)).Times(1);
    cmd->request_cmd();

    delete cmd;
}