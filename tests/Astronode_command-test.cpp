#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "Astronode_command.h"
#include "Transport_layer.h"


TEST(AstronodeCmdTest, get_answer_error_code_test){
    auto cmd = new Astronode_command();
    Transport_layer::answer_t cmd_ans;

    // no error
    cmd_ans.error_code = Transport_layer::serial_port_error_code::NO_ERROR;
    cmd_ans.answer_id = 0x85;
    cmd_ans.answer_parameters = {0};
    ASSERT_EQ(Astronode_command::astronode_error_code::ASTRONODE_ERR_CODE_OK, cmd->get_answer_error_code(cmd_ans));

    // weird case, answer_id says error, but param says no error
    cmd_ans.answer_id = 0xff;
    cmd_ans.answer_parameters = {0x0, 0x0};
    ASSERT_EQ(Astronode_command::astronode_error_code::ASTRONODE_ERR_CODE_OK, cmd->get_answer_error_code(cmd_ans));

    // error code crc not valid
    cmd_ans.answer_id = 0xff;
    cmd_ans.answer_parameters = {0x0, 0x1};
    ASSERT_EQ(Astronode_command::astronode_error_code::ASTRONODE_ERR_CODE_CRC_NOT_VALID, cmd->get_answer_error_code(cmd_ans));

    // error code no clear
    cmd_ans.answer_id = 0xff;
    cmd_ans.answer_parameters =  {0x46, 0x01};
    ASSERT_EQ(Astronode_command::astronode_error_code::ASTRONODE_ERR_CODE_NO_CLEAR, cmd->get_answer_error_code(cmd_ans));

    // TODO test all error codes

    delete cmd;
}

TEST(AstronodeCmdTest, cfg_w_build_command_test){
    auto cmd = new Astronode_command();
    std::vector<uint8_t> expected_ans = {0x05, 0x03, 0x0, 0x03};

    ASSERT_EQ(expected_ans, cmd->cfg_w_build_command(1, 1, 0, 0, 1, 1));
    delete cmd;
}

TEST(AstronodeCmdTest, wif_w_build_command_test){
    auto cmd = new Astronode_command();

    uint8_t wlan_ssid[SSID_LENGTH] = {0x6D, 0x79, 0x5F, 0x77, 0x69, 0x66, 0x69, 0x5F, 0x73, 0x73,0x69, 0x64};
    uint8_t wlan_key[PASSWORD_LENGTH] = {0x6D, 0x79, 0x5F, 0x77, 0x69, 0x66, 0x69, 0x5F, 0x70, 0x61,0x73, 0x73, 0x77, 0x6F, 0x72, 0x64};
    uint8_t auth_token[TOKEN_LENGTH] = {0x36, 0x6E, 0x78, 0x47, 0x52, 0x34, 0x65, 0x57, 0x59, 0x62, 0x34, 0x52, 0x38, 0x66, 0x45, 0x73, 0x58, 0x78, 0x32, 0x68, 0x31, 0x68, 0x47, 0x6F, 0x52, 0x36, 0x6E, 0x76, 0x6B, 0x75, 0x32, 0x54, 0x76, 0x47, 0x76, 0x54, 0x75, 0x46, 0x7A, 0x78, 0x69, 0x47, 0x59, 0x50, 0x70, 0x49, 0x43, 0x41, 0x41, 0x72, 0x6F, 0x5A, 0x4B, 0x74, 0x74, 0x48, 0x6E, 0x7A, 0x58, 0x54, 0x51, 0x53, 0x4C, 0x45, 0x69, 0x6C, 0x76, 0x43, 0x54, 0x54, 0x37, 0x72, 0x37, 0x45, 0x37, 0x75, 0x72, 0x5A, 0x37, 0x69, 0x45, 0x57, 0x34, 0x32, 0x66, 0x64, 0x69, 0x62, 0x6D, 0x58, 0x47, 0x34, 0x52, 0x4F, 0x51, 0x7A};

    std::vector<uint8_t> expected_ans = {0x06};
    expected_ans.insert(expected_ans.end(), &wlan_ssid[0], &wlan_ssid[SSID_LENGTH]);
    expected_ans.insert(expected_ans.end(), &wlan_key[0], &wlan_key[PASSWORD_LENGTH]);
    expected_ans.insert(expected_ans.end(), &auth_token[0], &auth_token[TOKEN_LENGTH]);

    ASSERT_EQ(expected_ans, cmd->wif_w_build_command("my_wifi_ssid", "my_wifi_password", "6nxGR4eWYb4R8fEsXx2h1hGoR6nvku2TvGvTuFzxiGYPpICAAroZKttHnzXTQSLEilvCTT7r7E7urZ7iEW42fdibmXG4ROQz"));

    delete cmd;
}

TEST(AstronodeCmdTest, ssc_w_build_command_test){
    auto cmd = new Astronode_command();

    std::vector<uint8_t> expected_ans = {0x07, 0x12, 0x1};
    ASSERT_EQ(expected_ans, cmd->ssc_w_build_command(0x12, 1));

    expected_ans.at(2) = 0x0;
    ASSERT_EQ(expected_ans, cmd->ssc_w_build_command(0x12, 0));

    delete cmd;
}

TEST(AstonodeCmdTest, cfg_s_build_command_test){
    auto cmd = new Astronode_command();

    std::vector<uint8_t> expected_ans = {0x10};
    ASSERT_EQ(expected_ans, cmd->cfg_s_build_command());
    delete cmd;
}

TEST(AstronodeCmdTest, cfg_f_build_command_test){
    auto cmd = new Astronode_command();

    std::vector<uint8_t> expected_ans = {0x11};
    ASSERT_EQ(expected_ans, cmd->cfg_f_build_command());
    delete cmd;
}

TEST(AstronodeCmdTest, cfg_r_build_command_test){
    auto cmd = new Astronode_command();
    std::vector<uint8_t> expected_ans = {0x15};
    ASSERT_EQ(expected_ans, cmd->cfg_r_build_command());
    delete cmd;
}

TEST(AstronodeCmdTest, cfg_r_get_product_id_test){
    auto cmd = new Astronode_command();
    std::vector<uint8_t> astronode_response = {0x03, 0x01, 0x02, 0x01, 0x00, 0x05, 0x00, 0x01};
    ASSERT_EQ(0x03, cmd->cfg_r_get_product_id(astronode_response));
    delete cmd;
}

TEST(AstronodeCmdTest, cfg_r_get_hardware_revision_test){
    auto cmd = new Astronode_command();
    std::vector<uint8_t> astronode_response = {0x03, 0x01, 0x02, 0x01, 0x00, 0x05, 0x00, 0x01};
    ASSERT_EQ(0x01, cmd->cfg_r_get_hardware_revision(astronode_response));
    delete cmd;
}

TEST(AstronodeCmdTest, cfg_r_get_firmware_major_version_test){
    auto cmd = new Astronode_command();
    std::vector<uint8_t> astronode_response = {0x03, 0x01, 0x02, 0x01, 0x00, 0x05, 0x00, 0x01};
    ASSERT_EQ(0x02, cmd->cfg_r_get_firmware_major_version(astronode_response));
    delete cmd;
}

TEST(AstronodeCmdTest, cfg_r_get_firmware_minor_version_test){
    auto cmd = new Astronode_command();
    std::vector<uint8_t> astronode_response = {0x03, 0x01, 0x02, 0x01, 0x00, 0x05, 0x00, 0x01};
    ASSERT_EQ(0x01, cmd->cfg_r_get_firmware_minor_version(astronode_response));
    delete cmd;
}

TEST(AstronodeCmdTest, cfg_r_get_firmware_revision_test){
    auto cmd = new Astronode_command();
    std::vector<uint8_t> astronode_response = {0x03, 0x01, 0x02, 0x01, 0x00, 0x05, 0x00, 0x01};
    ASSERT_EQ(0x00, cmd->cfg_r_get_firmware_revision(astronode_response));
    delete cmd;
}

TEST(AstronodeCmdTest, cfg_r_get_payload_ack_test){
    auto cmd = new Astronode_command();

    // payload ack is true
    std::vector<uint8_t> astronode_response = {0x03, 0x01, 0x02, 0x01, 0x00, 0x01, 0x00, 0x01};
    ASSERT_TRUE(cmd->cfg_r_get_payload_ack(astronode_response));

    // payload ack is false
    astronode_response = {0x03, 0x01, 0x02, 0x01, 0x00, 0x00, 0x00, 0x01};
    ASSERT_FALSE(cmd->cfg_r_get_payload_ack(astronode_response));
    delete cmd;
}

TEST(AstronodeCmdTest, cfg_r_get_add_geolocation_test){
    auto cmd = new Astronode_command();

    // add geolocation is true
    std::vector<uint8_t> astronode_response =  {0x03, 0x01, 0x02, 0x01, 0x00, 0x02, 0x00, 0x01};
    ASSERT_TRUE(cmd->cfg_r_get_add_geolocation(astronode_response));

    // add geolocation is false
    astronode_response =  {0x03, 0x01, 0x02, 0x01, 0x00, 0x00, 0x00, 0x01};
    ASSERT_FALSE(cmd->cfg_r_get_add_geolocation(astronode_response));
    delete cmd;
}

TEST(AstronodeCmdTest, cfg_r_get_ephemeris_enabled_test){
    auto cmd = new Astronode_command();

    // ephemeris enabled is true
    std::vector<uint8_t> astronode_response = {0x03, 0x01, 0x02, 0x01, 0x00, 0x04, 0x00, 0x01};
    ASSERT_TRUE(cmd->cfg_r_get_ephemeris_enabled(astronode_response));

    // ephemeris enabled is false
    astronode_response = {0x03, 0x01, 0x02, 0x01, 0x00, 0x00, 0x00, 0x01};
    ASSERT_FALSE(cmd->cfg_r_get_ephemeris_enabled(astronode_response));
    delete cmd;
}

TEST(AstronodeCmdTest, cfg_r_get_deep_sleep_enabled_test){
    auto cmd = new Astronode_command();

    // deep sleep enabled is true
    std::vector<uint8_t> astronode_response = {0x03, 0x01, 0x02, 0x01, 0x00, 0x08, 0x00, 0x01};
    ASSERT_TRUE(cmd->cfg_r_get_deep_sleep_enabled(astronode_response));

    // deep sleep enabled is false
    astronode_response = {0x03, 0x01, 0x02, 0x01, 0x00, 0x00, 0x00, 0x01};
    ASSERT_FALSE(cmd->cfg_r_get_deep_sleep_enabled(astronode_response));
    delete cmd;
}

TEST(AstronodeCmdTest, cfg_r_get_payload_ack_evt_pin_enabled_test){
    auto cmd = new Astronode_command();

    // payload ack evt pin enabled is true
    std::vector<uint8_t> astronode_response = {0x03, 0x01, 0x02, 0x01, 0x00, 0x08, 0x00, 0x01};
    ASSERT_TRUE(cmd->cfg_r_get_payload_ack_evt_pin_enabled(astronode_response));

    // payload ack evt pin enabled is false
    astronode_response = {0x03, 0x01, 0x02, 0x01, 0x00, 0x00, 0x00, 0x00};
    ASSERT_FALSE(cmd->cfg_r_get_payload_ack_evt_pin_enabled(astronode_response));
    delete cmd;
}

TEST(AstronodeCmdTest, cfg_r_get_reset_notification_evt_pin_enabled_test){
    auto cmd = new Astronode_command();

    // reset notification evt pin enabled is true
    std::vector<uint8_t> astronode_response = {0x03, 0x01, 0x02, 0x01, 0x00, 0x08, 0x00, 0x02};
    ASSERT_TRUE(cmd->cfg_r_get_reset_notification_evt_pin_enabled(astronode_response));

    // reset notification evt pin enabled is false
    astronode_response = {0x03, 0x01, 0x02, 0x01, 0x00, 0x00, 0x00, 0x00};
    ASSERT_FALSE(cmd->cfg_r_get_reset_notification_evt_pin_enabled(astronode_response));

    delete cmd;
}

TEST(AstronodeCmdTest, cfg_r_get_command_available_evt_pin_enabled_test){
    auto cmd = new Astronode_command();

    // command available evt pin enabled is true
    std::vector<uint8_t> astronode_response = {0x03, 0x01, 0x02, 0x01, 0x00, 0x08, 0x00, 0x04};
    ASSERT_TRUE(cmd->cfg_r_get_command_available_evt_pin_enabled(astronode_response));

    // command available evt pin enabled is false
    astronode_response = {0x03, 0x01, 0x02, 0x01, 0x00, 0x00, 0x00, 0x00};
    ASSERT_FALSE(cmd->cfg_r_get_command_available_evt_pin_enabled(astronode_response));
    delete cmd;
}

TEST(AstronodeCmdTest, cfg_r_get_message_transmission_pending_evt_pin_enabled_test){
    auto cmd = new Astronode_command();

    // message transmission pending evt pin enabled is true
    std::vector<uint8_t> astronode_response = {0x03, 0x01, 0x02, 0x01, 0x00, 0x08, 0x00, 0x08};
    ASSERT_TRUE(cmd->cfg_r_get_message_transmission_pending_evt_pin_enabled(astronode_response));

    // message transmission pending evt pin enabled is false
    astronode_response = {0x03, 0x01, 0x02, 0x01, 0x00, 0x00, 0x00, 0x00};
    ASSERT_FALSE(cmd->cfg_r_get_message_transmission_pending_evt_pin_enabled(astronode_response));
    delete cmd;
}










