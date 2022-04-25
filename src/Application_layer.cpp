#include <iostream>
#include  <iomanip>

#include "Application_layer.h"

Application_layer::Application_layer(std::shared_ptr<Transport_layer> tr) : tr_(std::move(tr)){}

void Application_layer::request_cmd(const std::vector<uint8_t> command){
    for(int i = 0; i < command.size(); i++){
        std::cout<<"0x"<<std::hex<<(int)command.at(i);
        if(i<command.size() - 1){
            std::cout<<",";
        }
    }
    std::cout<<std::endl;
    Transport_layer::Command_t ans = tr_->request_command(command);
    command_id_sent_ = command.at(0);
    decoded_command_parameters_ = ans.command_parameters;
    decoded_command_id_ = ans.command_id;
    decoded_answer_checksum_ = ans.command_checksum;
    decoded_answer_error_code_ = ans.error_code;
    request_sent_ = true;
}

bool Application_layer::get_answer_success() {
    if(request_sent_ == false){
        std::cout << "request was not sent" <<std::endl;
        return false;
    }

    // check transport layer error code
    if(decoded_answer_error_code_ != Transport_layer::NO_ERROR){
        return false;
    }

    // check error id
    if((command_id_sent_ + 0x80) != decoded_command_id_){
        return false;
    }

    return true;
}

std::vector<uint8_t> Application_layer::get_answer_parameters(void){
    if(request_sent_ == false){
        std::cout << "request was not sent" << std::endl;
        return {};
    }
    return decoded_command_parameters_;
}

void Command_cfg_w::request_cmd(uint8_t payload_ack_bit, uint8_t add_geo_bit, uint8_t enable_ephemeris_bit, uint8_t deep_sleep_enabled_bit, uint8_t payload_ack_evt_pin_bit, uint8_t reset_notif_evt_pin_bit){
    std::cout << __PRETTY_FUNCTION__ <<std::endl;
    uint8_t byte0 = ((deep_sleep_enabled_bit & 0x01) << 3) | ((enable_ephemeris_bit & 0x01)<<2) | ((add_geo_bit & 0x01)<<1) | (payload_ack_bit & 0x01);
    uint8_t byte1 = 0;
    uint8_t byte2 = ((reset_notif_evt_pin_bit & 0x01)<<1) | (payload_ack_evt_pin_bit & 0x01);
    std::vector<uint8_t> data = {0x05, byte0, byte1, byte2};
    Application_layer::request_cmd(data);
}

void Command_wif_w::request_cmd(std::string wlan_ssid, std::string wlan_key, std::string auth_token) {
    std::cout << __PRETTY_FUNCTION__ <<std::endl;
    wlan_ssid.insert(wlan_ssid.end(), SSID_LENGTH - wlan_ssid.size(), '\0');    // zeros padding
    wlan_key.insert(wlan_key.end(), PASSWORD_LENGTH - wlan_key.size(), '\0');   // zeros padding
    auth_token.insert(auth_token.end(), TOKEN_LENGTH - auth_token.size(), '\0');// zeros padding
    std::string tmp_data = wlan_ssid + wlan_key + auth_token;
    std::vector<uint8_t> data(tmp_data.begin(), tmp_data.end());
    data.insert(data.begin(), 0x06);
    Application_layer::request_cmd(data);
}

void Command_ssc_w::request_cmd(uint8_t sat_period_enum, uint8_t enable_search) {
    std::cout << __PRETTY_FUNCTION__ <<std::endl;
    std::vector<uint8_t> data = {0x07};
    data.insert(data.end(), sat_period_enum);
    data.insert(data.end(), enable_search == 1 ? 1 : 0);
    Application_layer::request_cmd(data);
}

void Command_cfg_s::request_cmd(void) {
    std::cout << __PRETTY_FUNCTION__ <<std::endl;
    std::vector<uint8_t> data = {0x10};
    Application_layer::request_cmd(data);
}

void Command_cfg_f::request_cmd(void) {
    std::cout << __PRETTY_FUNCTION__ <<std::endl;
    std::vector<uint8_t> data = {0x11};
    Application_layer::request_cmd(data);
}

void Command_cfg_r::request_cmd(void) {
    std::cout << __PRETTY_FUNCTION__ <<std::endl;
    std::vector<uint8_t> data = {0x15};
    Application_layer::request_cmd(data);
}

//std::vector<uint8_t> Command_cfg_r::get_answer_parameters(void){
//    std::cout << __PRETTY_FUNCTION__ <<std::endl;
//    return Application_layer::get_answer_parameters();
//}

uint8_t Command_cfg_r::get_product_id(void){
    throw "myFunction is not implemented yet.";
}

uint8_t Command_cfg_r::get_hardware_revision(void){
    throw "myFunction is not implemented yet.";
}

uint8_t Command_cfg_r::get_firmware_major_version(void){
    throw "myFunction is not implemented yet.";
}

uint8_t Command_cfg_r::get_firmware_minor_version(void){
    throw "myFunction is not implemented yet.";
}

uint8_t Command_cfg_r::get_firmware_revision(void){
    throw "myFunction is not implemented yet.";
}

bool Command_cfg_r::get_payload_ack(void){
    throw "myFunction is not implemented yet.";
}

bool Command_cfg_r::get_add_geolocation(void){
    throw "myFunction is not implemented yet.";
}

bool Command_cfg_r::get_ephemeris_enabled(void){
    throw "myFunction is not implemented yet.";
}

bool Command_cfg_r::get_deep_sleep_enabled(void){
    throw "myFunction is not implemented yet.";
}

bool Command_cfg_r::get_payload_ack_evt_pin_enabled(void){
    throw "myFunction is not implemented yet.";
}

bool Command_cfg_r::get_reset_notification_evt_pin_enabled(void){
    throw "myFunction is not implemented yet.";
}

bool Command_cfg_r::get_command_available_evt_pin_enabled(void){
    throw "myFunction is not implemented yet.";
}

bool Command_cfg_r::get_message_transmission_pending_evt_pin_enabled(void){
    throw "myFunction is not implemented yet.";
}

void Command_rtc_r::request_cmd(void) {
    std::cout << __PRETTY_FUNCTION__ <<std::endl;
    std::vector<uint8_t> data = {0x17};
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
    std::vector<uint8_t> data = {0x18};
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
    std::vector<uint8_t> data = {0x19};
    Application_layer::request_cmd(data);
}

void Command_msn_r::request_cmd(void) {
    std::cout << __PRETTY_FUNCTION__ <<std::endl;
    std::vector<uint8_t> data = {0x1A};
    Application_layer::request_cmd(data);
}

void Command_mpn_r::request_cmd(void) {
    std::cout << __PRETTY_FUNCTION__ <<std::endl;
    std::vector<uint8_t> data = {0x1B};
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
    data.insert(data.begin(), 0x25);
    Application_layer::request_cmd(data);
}

uint16_t Command_pld_e::get_command_id(void) {
    // ex.  {0x03, 0xE9} = 0x03E9 = 1001
    std::vector<uint8_t> ans_v = Application_layer::get_answer_parameters();
    return  (ans_v.at(0) << 8) + ans_v.at(1);;
}

void Command_pld_d::request_cmd(void){
    std::cout << __PRETTY_FUNCTION__ <<std::endl;
    std::vector<uint8_t> data = {0x26};
    Application_layer::request_cmd(data);
}

uint16_t Command_pld_d::get_command_id(void) {
    // ex.  {0x03, 0xE9} = 0x03E9 = 1001
    std::vector<uint8_t> ans_v = Application_layer::get_answer_parameters();
    return  (ans_v.at(0) << 8) + ans_v.at(1);;
}

void Command_pld_f::request_cmd(void) {
    std::cout << __PRETTY_FUNCTION__ <<std::endl;
    std::vector<uint8_t> data = {0x27};
    Application_layer::request_cmd(data);
}

void Command_geo_w::request_cmd(std::string lat, std::string lng) {
    throw "myFunction is not implemented yet.";
}

void Command_evt_r::request_cmd(void) {
    std::cout << __PRETTY_FUNCTION__ <<std::endl;
    std::vector<uint8_t> data = {0x65};
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
    std::vector<uint8_t> data = {0x45};
    Application_layer::request_cmd(data);
}

uint16_t Command_sak_r::get_command_id(void) {
    // ex.  {0x03, 0xE9} = 0x03E9 = 1001
    std::vector<uint8_t> ans_v = Application_layer::get_answer_parameters();
    return  (ans_v.at(0) << 8) + ans_v.at(1);;
}

void Command_sak_c::request_cmd(void) {
    std::cout << __PRETTY_FUNCTION__ <<std::endl;
    std::vector<uint8_t> data = {0x46};
    Application_layer::request_cmd(data);
}

void Command_cmd_r::request_cmd(void) {
    std::cout << __PRETTY_FUNCTION__ <<std::endl;
    std::vector<uint8_t> data = {0x47};
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
    std::vector<uint8_t> data = {0x48};
    Application_layer::request_cmd(data);
}

void Command_res_c::request_cmd(void) {
    std::cout << __PRETTY_FUNCTION__ <<std::endl;
    std::vector<uint8_t> data = {0x55};
    Application_layer::request_cmd(data);
}