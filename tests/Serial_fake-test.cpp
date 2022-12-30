#include "gtest/gtest.h"
//#include "gmock/gmock.h"
#include "Serial_fake/Serial_fake.h"
#include "Astronode_command.h"
#include "Transport_layer.h"
#include "Opcodes_id.h"


TEST(SerialFakeTests, cfg_w_test){
    std::vector<uint8_t> expected_ans = {};
    std::shared_ptr<Transport_layer> tr = std::make_shared<Transport_layer>("port");
    auto cmd = new Astronode_command(tr);
    astronode_answer_t ans = cmd->cfg_w( 1, 1, 0, 0, 1, 1);
    ASSERT_EQ(expected_ans, ans.answer_parameters);
    ASSERT_EQ(Transport_layer::serial_port_error_code_t::NO_ERROR, ans.error_code);
    ASSERT_EQ(Astronode_command::ASTRONODE_ERR_CODE_OK, cmd->get_answer_error_code(ans));
}

TEST(SerialFakeTests, cfg_r_test){
    std::vector<uint8_t> expected_ans = {1, 2, 3, 4, 5, 6, 7, 8};
    std::shared_ptr<Transport_layer> tr = std::make_shared<Transport_layer>("port");
    auto cmd = new Astronode_command(tr);
    astronode_answer_t ans = cmd->cfg_r();
    ASSERT_EQ(expected_ans, ans.answer_parameters);
    ASSERT_EQ(Transport_layer::serial_port_error_code_t::NO_ERROR, ans.error_code);
    ASSERT_EQ(Astronode_command::ASTRONODE_ERR_CODE_OK, cmd->get_answer_error_code(ans));
}

TEST(SerialFakeTests, wif_w_test){
    std::vector<uint8_t> expected_ans = {};
    std::shared_ptr<Transport_layer> tr = std::make_shared<Transport_layer>("port");
    auto cmd = new Astronode_command(tr);
    astronode_answer_t ans = cmd->wif_w("wlan_ssid", "wlan_key", "auth_token");
    ASSERT_EQ(expected_ans, ans.answer_parameters);
    ASSERT_EQ(Transport_layer::serial_port_error_code_t ::NO_ERROR, ans.error_code);
    ASSERT_EQ(Astronode_command::ASTRONODE_ERR_CODE_OK, cmd->get_answer_error_code(ans));
}

TEST(SerialFakeTests, ssc_w_void_answer_test){
    std::vector<uint8_t> expected_ans = {};
    std::shared_ptr<Transport_layer> tr = std::make_shared<Transport_layer>("port");
    auto cmd = new Astronode_command(tr);
    astronode_answer_t ans = cmd->ssc_w(0,0);
    ASSERT_EQ(expected_ans, ans.answer_parameters);
    ASSERT_EQ(Transport_layer::serial_port_error_code_t::NO_ERROR, ans.error_code);
    ASSERT_EQ(Astronode_command::ASTRONODE_ERR_CODE_OK, cmd->get_answer_error_code(ans));
}

// TODO test cfg_s fake
// TODO test cfg_f fake
// TODO test cfg_r fake
// TODO test rtc_r fake
// TODO test nco_r fake
// TODO test mgi_r fake
// TODO test msn_r fake
// TODO test mpn_r fake
// TODO test pld_e fake
// TODO test pld_d fake
// TODO test pld_f fake
// TODO test geo_w fake
// TODO test sak_r fake
// TODO test sak_c fake
// TODO test cmd_r fake
// TODO test cmd_c fake
// TODO test res_c fake
// TODO test val_w fake
// TODO test ttx_s fake
// TODO Test gpo_s fake
// TODO test gpi_r fake
// TODO Test adc_r fake
// TODO Test evt_r fake
// TODO test ctx_s fake
// TODO test per_r fake
// TODO test per_c fake
// TODO test mst_r fake
// TODO test lcd_r fake
// TODO test end_r fake
// TODO test htx_s fake
