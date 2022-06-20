#include "gtest/gtest.h"
//#include "gmock/gmock.h"
#include "Serial_fake/Serial_fake.h"
#include "Application_layer.h"
//#include "Transport_layer.h"

TEST(SerialFakeTests, cfg_w_test){
    std::vector<uint8_t> expected_ans = {};
    std::shared_ptr<Transport_layer> tr = std::make_shared<Transport_layer>("port");
    auto cmd = new Command_cfg_w(tr);
    cmd->request_cmd(1, 1, 0, 0, 1, 1);
    ASSERT_EQ(expected_ans, cmd->get_answer_parameters());
    ASSERT_EQ(true, cmd->get_answer_success());
}

TEST(SerialFakeTests, wif_w_test){
    std::vector<uint8_t> expected_ans = {};
    std::shared_ptr<Transport_layer> tr = std::make_shared<Transport_layer>("port");
    auto cmd = new Command_wif_w(tr);
    cmd->request_cmd("wlan_ssid", "wlan_key", "auth_token");
    ASSERT_EQ(expected_ans, cmd->get_answer_parameters());
    ASSERT_EQ(true, cmd->get_answer_success());
}

TEST(SerialFakeTests, ssc_w_void_answer_test){
    std::vector<uint8_t> expected_ans = {};
    std::shared_ptr<Transport_layer> tr = std::make_shared<Transport_layer>("port");
    auto cmd = new Command_ssc_w(tr);
    cmd->request_cmd(0, 0);
 //   ASSERT_EQ(expected_ans, cmd->get_answer_parameters());
    ASSERT_EQ(false, cmd->get_answer_success());
//    ASSERT_EQ(Transport_layer::serial_error_code_t::NO_VALUE_ERROR, cmd->get_answer_error_code());
}

// TODO test ssc_w fake
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
