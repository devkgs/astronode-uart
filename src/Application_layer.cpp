#include <iostream>
#include  <iomanip>

#include "Application_layer.h"
#include "Opcodes_id.h"

Application_layer::Application_layer(std::shared_ptr<Transport_layer> tr) : tr_(std::move(tr)){}

void Application_layer::request_cmd(const std::vector<uint8_t> command){
    std::cout<<"Application_layer::request_cmd"<<std::endl;
    for(int i = 0; i < command.size(); i++){
        std::cout<<"0x"<<std::hex<<(int)command.at(i);
        if(i<command.size() - 1){
            std::cout<<",";
        }
    }
    std::cout<<std::endl;
    Transport_layer::answer_t ans = tr_->request_command(command);
    command_id_sent_ = command.at(0);
    decoded_answer_parameters_ = ans.answer_parameters;
    decoded_answer_command_id_ = ans.answer_id;
    decoded_answer_checksum_ = ans.answer_checksum;
    transport_layer_error_ = ans.error_code;
    request_sent_ = true;
}

std::vector<uint8_t> Application_layer::get_answer_parameters(void){
    if(request_sent_ == false){
        std::cout << "request was not sent" << std::endl;
        return {};
    }
    return decoded_answer_parameters_;
}

Application_layer::astronode_error_code Application_layer::get_answer_error_code(){
    if(request_sent_ == false){
        std::cout << "request was not sent" << std::endl;
        return ASTRONODE_ERR_CODE_OK;   // not ok but no other value in astronode_error_code
    }

    if(decoded_answer_command_id_ == 0xFF){
        // TODO check param size
        uint16_t error_code = (decoded_answer_parameters_.at(0) << 8 ) | decoded_answer_parameters_.at(1);
        std::cout<<"error code = "<<error_code<<std::endl;
        return static_cast<Application_layer::astronode_error_code> (error_code);
    } else{
        return ASTRONODE_ERR_CODE_OK;
    }
}

serial_port_error_code_t Application_layer::get_serial_port_error_code(){
    if(request_sent_ == false){
        return serial_port_error_code_t::NO_REQUEST_SENT;
    }
    return static_cast<serial_port_error_code> (transport_layer_error_);
}

void Command_cfg_w::request_cmd(uint8_t payload_ack_bit, uint8_t add_geo_bit, uint8_t enable_ephemeris_bit, uint8_t deep_sleep_enabled_bit, uint8_t payload_ack_evt_pin_bit, uint8_t reset_notif_evt_pin_bit){
    std::cout << __PRETTY_FUNCTION__ <<std::endl;
    uint8_t byte0 = ((deep_sleep_enabled_bit & 0x01) << 3) | ((enable_ephemeris_bit & 0x01)<<2) | ((add_geo_bit & 0x01)<<1) | (payload_ack_bit & 0x01);
    uint8_t byte1 = 0;
    uint8_t byte2 = ((reset_notif_evt_pin_bit & 0x01)<<1) | (payload_ack_evt_pin_bit & 0x01);
    std::vector<uint8_t> data = {ASTRONODE_OP_CODE_CFG_WR, byte0, byte1, byte2};
    Application_layer::request_cmd(data);
}

void Command_wif_w::request_cmd(std::string wlan_ssid, std::string wlan_key, std::string auth_token) {
    std::cout << __PRETTY_FUNCTION__ <<std::endl;
    wlan_ssid.insert(wlan_ssid.end(), SSID_LENGTH - wlan_ssid.size(), '\0');    // zeros padding
    wlan_key.insert(wlan_key.end(), PASSWORD_LENGTH - wlan_key.size(), '\0');   // zeros padding
    auth_token.insert(auth_token.end(), TOKEN_LENGTH - auth_token.size(), '\0');// zeros padding
    std::string tmp_data = wlan_ssid + wlan_key + auth_token;
    std::vector<uint8_t> data(tmp_data.begin(), tmp_data.end());
    data.insert(data.begin(), ASTRONODE_OP_CODE_WIF_WR);
    Application_layer::request_cmd(data);
}

void Command_ssc_w::request_cmd(uint8_t sat_period_enum, uint8_t enable_search) {
    std::cout << __PRETTY_FUNCTION__ <<std::endl;
    std::vector<uint8_t> data = {ASTRONODE_OP_CODE_SSC_WR};
    data.insert(data.end(), sat_period_enum);
    data.insert(data.end(), enable_search == 1 ? 1 : 0);
    Application_layer::request_cmd(data);
}

void Command_cfg_s::request_cmd(void) {
    std::cout << __PRETTY_FUNCTION__ <<std::endl;
    std::vector<uint8_t> data = {ASTRONODE_OP_CODE_CFG_SR};
    Application_layer::request_cmd(data);
}

void Command_cfg_f::request_cmd(void) {
    std::cout << __PRETTY_FUNCTION__ <<std::endl;
    std::vector<uint8_t> data = {ASTRONODE_OP_CODE_CFG_FR};
    Application_layer::request_cmd(data);
}

void Command_cfg_r::request_cmd(void) {
    std::cout << __PRETTY_FUNCTION__ <<std::endl;
    std::vector<uint8_t> data = {ASTRONODE_OP_CODE_CFG_RR};
    Application_layer::request_cmd(data);
}

//std::vector<uint8_t> Command_cfg_r::get_answer_parameters(void){
//    std::cout << __PRETTY_FUNCTION__ <<std::endl;
//    return Application_layer::get_answer_parameters();
//}

uint8_t Command_cfg_r::get_product_id(void){
    std::vector<uint8_t> ans_v = Application_layer::get_answer_parameters();
    return  ans_v.at(0);
//    throw "myFunction is not implemented yet.";
}

uint8_t Command_cfg_r::get_hardware_revision(void){
    std::vector<uint8_t> ans_v = Application_layer::get_answer_parameters();
    return  ans_v.at(1);
}

uint8_t Command_cfg_r::get_firmware_major_version(void){
    std::vector<uint8_t> ans_v = Application_layer::get_answer_parameters();
    return  ans_v.at(2);
}

uint8_t Command_cfg_r::get_firmware_minor_version(void){
    std::vector<uint8_t> ans_v = Application_layer::get_answer_parameters();
    return  ans_v.at(3);
}

uint8_t Command_cfg_r::get_firmware_revision(void){
    std::vector<uint8_t> ans_v = Application_layer::get_answer_parameters();
    return  ans_v.at(4);
}

bool Command_cfg_r::get_payload_ack(void){
    std::vector<uint8_t> ans_v = Application_layer::get_answer_parameters();
    return  ans_v.at(5) & 1;
}

bool Command_cfg_r::get_add_geolocation(void){
    std::vector<uint8_t> ans_v = Application_layer::get_answer_parameters();
    return  ans_v.at(5) & 2;
}

bool Command_cfg_r::get_ephemeris_enabled(void){
    std::vector<uint8_t> ans_v = Application_layer::get_answer_parameters();
    return  ans_v.at(5) & 4;
}

bool Command_cfg_r::get_deep_sleep_enabled(void){
    std::vector<uint8_t> ans_v = Application_layer::get_answer_parameters();
    return  ans_v.at(5) & 8;
}

bool Command_cfg_r::get_payload_ack_evt_pin_enabled(void){
    std::vector<uint8_t> ans_v = Application_layer::get_answer_parameters();
    return  ans_v.at(7) & 1;
}

bool Command_cfg_r::get_reset_notification_evt_pin_enabled(void){
    std::vector<uint8_t> ans_v = Application_layer::get_answer_parameters();
    return  ans_v.at(7) & 2;
}

bool Command_cfg_r::get_command_available_evt_pin_enabled(void){
    std::vector<uint8_t> ans_v = Application_layer::get_answer_parameters();
    return  ans_v.at(7) & 4;
}

bool Command_cfg_r::get_message_transmission_pending_evt_pin_enabled(void){
    std::vector<uint8_t> ans_v = Application_layer::get_answer_parameters();
    return  ans_v.at(7) & 8;
}

void Command_rtc_r::request_cmd(void) {
    std::cout << __PRETTY_FUNCTION__ <<std::endl;
    std::vector<uint8_t> data = {ASTRONODE_OP_CODE_RTC_RR};
    Application_layer::request_cmd(data);
}

//std::vector<uint8_t> Command_rtc_r::get_answer_parameters(void){
//    std::cout << __PRETTY_FUNCTION__ <<std::endl;
//    return Application_layer::get_answer_parameters();
//}

uint32_t Command_rtc_r::get_rtc_time(void) {
    //std::vector<uint8_t> answer_data = Application_layer::get_answer_parameters();
    throw "myFunction is not implemented yet.";
}

void Command_nco_r::request_cmd(void) {
    std::cout << __PRETTY_FUNCTION__ <<std::endl;
    std::vector<uint8_t> data = {ASTRONODE_OP_CODE_NCO_RR};
    Application_layer::request_cmd(data);
}

//std::vector<uint8_t> Command_nco_r::get_answer_parameters(void){
//    std::cout << __PRETTY_FUNCTION__ <<std::endl;
//    return Application_layer::get_answer_parameters();
//}

uint32_t Command_nco_r::get_time_to_next_pass(void){
    throw "myFunction is not implemented yet.";
}

void Command_mgi_r::request_cmd(void) {
    std::cout << __PRETTY_FUNCTION__ <<std::endl;
    std::vector<uint8_t> data = {ASTRONODE_OP_CODE_DGI_RR};
    Application_layer::request_cmd(data);
}

void Command_msn_r::request_cmd(void) {
    std::cout << __PRETTY_FUNCTION__ <<std::endl;
    std::vector<uint8_t> data = {ASTRONODE_OP_CODE_DSN_RR};
    Application_layer::request_cmd(data);
}

void Command_mpn_r::request_cmd(void) {
    std::cout << __PRETTY_FUNCTION__ <<std::endl;
    std::vector<uint8_t> data = {ASTRONODE_OP_CODE_MPN_RR};
    Application_layer::request_cmd(data);
}

void Command_pld_e::request_cmd(uint16_t payload_id, const std::string payload_data) {
    std::cout << __PRETTY_FUNCTION__ <<std::endl;

    // payload_id is converted into two characters. ex. 1001 = 0x03E9 = {0x03, 0xE9}
    std::string s_payload_id;
    s_payload_id.resize(2);
    s_payload_id[0] = (uint8_t)(payload_id>>8);
    s_payload_id[1] = (uint8_t)(payload_id & 0xFF);

    std::string tmp_data = s_payload_id + payload_data;
    std::vector<uint8_t> data(tmp_data.begin(), tmp_data.end());
    data.insert(data.begin(), ASTRONODE_OP_CODE_PLD_ER);
    Application_layer::request_cmd(data);
}

uint16_t Command_pld_e::get_command_id(void) {
    // ex.  {0x03, 0xE9} = 0x03E9 = 1001
    std::vector<uint8_t> ans_v = Application_layer::get_answer_parameters();
    return  (ans_v.at(0) << 8) + ans_v.at(1);
}

void Command_pld_d::request_cmd(void){
    std::cout << __PRETTY_FUNCTION__ <<std::endl;
    std::vector<uint8_t> data = {ASTRONODE_OP_CODE_PLD_DR};
    Application_layer::request_cmd(data);
}

uint16_t Command_pld_d::get_command_id(void) {
    // ex.  {0x03, 0xE9} = 0x03E9 = 1001
    std::vector<uint8_t> ans_v = Application_layer::get_answer_parameters();
    return  (ans_v.at(0) << 8) + ans_v.at(1);;
}

void Command_pld_f::request_cmd(void) {
    std::cout << __PRETTY_FUNCTION__ <<std::endl;
    std::vector<uint8_t> data = {ASTRONODE_OP_CODE_PLD_FR};
    Application_layer::request_cmd(data);
}

void Command_geo_w::request_cmd(int32_t lat, int32_t lng) {
    std::cout << __PRETTY_FUNCTION__ <<std::endl;
    std::vector<uint8_t> data = {ASTRONODE_OP_CODE_GEO_WR};

    for(int i = 0; i < 4; i++){
        data.insert(data.end(), (uint8_t) (lat >> (i * 8)));
    }

    for(int i = 0; i < 4; i++){
        data.insert(data.end(), (uint8_t) (lng >> (i * 8)));
    }

    Application_layer::request_cmd(data);
}

void Command_evt_r::request_cmd(void) {
    std::cout << __PRETTY_FUNCTION__ <<std::endl;
    std::vector<uint8_t> data = {ASTRONODE_OP_CODE_EVT_RR};
    Application_layer::request_cmd(data);
}

bool Command_evt_r::get_sak_available(void){
    std::vector<uint8_t> ans = Application_layer::get_answer_parameters();
    if(ans.size() != 1){
        throw "evt_ra wrong size";
    }
    return ans.back() & 0x1;
}

bool Command_evt_r::get_module_reset(void){
    std::vector<uint8_t> ans = Application_layer::get_answer_parameters();
    if(ans.size() != 1){
        throw "evt_ra wrong size";
    }
    return ans.back() & 0x2;
}

bool Command_evt_r::get_command_available(void){
    std::vector<uint8_t> ans = Application_layer::get_answer_parameters();
    if(ans.size() != 1){
        throw "evt_ra wrong size";
    }
    return ans.back() & 0x4;
}

bool Command_evt_r::get_message_transmit_pending(void){
    std::vector<uint8_t> ans = Application_layer::get_answer_parameters();
    if(ans.size() != 1){
        throw "evt_ra wrong size";
    }
    return ans.back() & 0x8;
}

void Command_sak_r::request_cmd(void) {
    std::cout << __PRETTY_FUNCTION__ <<std::endl;
    std::vector<uint8_t> data = {ASTRONODE_OP_CODE_SAK_RR};
    Application_layer::request_cmd(data);
}

uint16_t Command_sak_r::get_command_id(void) {
    // ex.  {0x03, 0xE9} = 0x03E9 = 1001
    std::vector<uint8_t> ans_v = Application_layer::get_answer_parameters();
    return  (ans_v.at(0) << 8) + ans_v.at(1);;
}

void Command_sak_c::request_cmd(void) {
    std::cout << __PRETTY_FUNCTION__ <<std::endl;
    std::vector<uint8_t> data = {ASTRONODE_OP_CODE_SAK_CR};
    Application_layer::request_cmd(data);
}

void Command_cmd_r::request_cmd(void) {
    std::cout << __PRETTY_FUNCTION__ <<std::endl;
    std::vector<uint8_t> data = {ASTRONODE_OP_CODE_CMD_RR};
    Application_layer::request_cmd(data);
}

uint32_t Command_cmd_r::get_created_date(void) {
    // 0x03C26700 becomes 63072000
    std::vector<uint8_t> ans_v = Application_layer::get_answer_parameters();
    uint32_t created_date = (uint32_t)ans_v.at(0) << 24;
    created_date += (uint32_t)ans_v.at(1)<<16;
    created_date += (uint32_t)ans_v.at(2)<<8;
    created_date += (uint32_t)ans_v.at(3);
    return created_date;
}

std::vector<uint8_t> Command_cmd_r::get_payload(void) {
    std::vector<uint8_t> ans_v = Application_layer::get_answer_parameters();
    std::vector<uint8_t> payload(ans_v.begin()+4, ans_v.end());
    return payload;
}

void Command_cmd_c::request_cmd(void) {
    std::cout << __PRETTY_FUNCTION__ <<std::endl;
    std::vector<uint8_t> data = {ASTRONODE_OP_CODE_CMD_CR};
    Application_layer::request_cmd(data);
}

void Command_res_c::request_cmd(void) {
    std::cout << __PRETTY_FUNCTION__ <<std::endl;
    std::vector<uint8_t> data = {ASTRONODE_OP_CODE_RES_CR};
    Application_layer::request_cmd(data);
}