#include "Astronode_command.h"
#include <iostream>

Astronode_command::Astronode_command(std::shared_ptr<Transport_layer> tr) : tr_(std::move(tr)){}


Astronode_command::astronode_error_code Astronode_command::get_answer_error_code(astronode_answer_t ans){
    if(ans.answer_id == 0xFF){
        // TODO check param size
        uint16_t error_code = (ans.answer_parameters.at(0) << 8 ) | ans.answer_parameters.at(1);
        return static_cast<Astronode_command::astronode_error_code> (error_code);
    } else{
        return ASTRONODE_ERR_CODE_OK;
    }
}

std::vector<uint8_t> Astronode_command::cfg_w(uint8_t payload_ack_bit, uint8_t add_geo_bit, uint8_t enable_ephemeris_bit, uint8_t deep_sleep_enabled_bit, uint8_t payload_ack_evt_pin_bit, uint8_t reset_notif_evt_pin_bit){
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    uint8_t byte0 = ((deep_sleep_enabled_bit & 0x01) << 3) | ((enable_ephemeris_bit & 0x01)<<2) | ((add_geo_bit & 0x01)<<1) | (payload_ack_bit & 0x01);
    uint8_t byte1 = 0;
    uint8_t byte2 = ((reset_notif_evt_pin_bit & 0x01)<<1) | (payload_ack_evt_pin_bit & 0x01);
    return {ASTRONODE_OP_CODE_CFG_WR, byte0, byte1, byte2};
}

std::vector<uint8_t> Astronode_command::wif_w_build_command(std::string wlan_ssid, std::string wlan_key, std::string auth_token){
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    wlan_ssid.insert(wlan_ssid.end(), SSID_LENGTH - wlan_ssid.size(), '\0');    // zeros padding
    wlan_key.insert(wlan_key.end(), PASSWORD_LENGTH - wlan_key.size(), '\0');   // zeros padding
    auth_token.insert(auth_token.end(), TOKEN_LENGTH - auth_token.size(), '\0');// zeros padding
    std::string tmp_data = wlan_ssid + wlan_key + auth_token;
    std::vector<uint8_t> data(tmp_data.begin(), tmp_data.end());
    data.insert(data.begin(), ASTRONODE_OP_CODE_WIF_WR);
    return data;
}

std::vector<uint8_t> Astronode_command::ssc_w_build_command(uint8_t sat_period_enum, uint8_t enable_search){
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    std::vector<uint8_t> data = {ASTRONODE_OP_CODE_SSC_WR};
    data.insert(data.end(), sat_period_enum);
    data.insert(data.end(), enable_search == 1 ? 1 : 0);
    return data;
}

std::vector<uint8_t> Astronode_command::cfg_s_build_command(void){
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    std::vector<uint8_t> data = {ASTRONODE_OP_CODE_CFG_SR};
    return data;
}

std::vector<uint8_t> Astronode_command::cfg_f_build_command(void){
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    std::vector<uint8_t> data = {ASTRONODE_OP_CODE_CFG_FR};
    return data;
}

std::vector<uint8_t> Astronode_command::cfg_r_build_command(void){
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    return {ASTRONODE_OP_CODE_CFG_RR};
}

uint8_t Astronode_command::cfg_r_get_product_id(std::vector<uint8_t> astronode_answer){
    return astronode_answer.at(0);
}

uint8_t Astronode_command::cfg_r_get_hardware_revision(std::vector<uint8_t> astronode_answer){
    return astronode_answer.at(1);
}

uint8_t Astronode_command::cfg_r_get_firmware_major_version(std::vector<uint8_t> astronode_answer){
    return astronode_answer.at(2);
}

uint8_t Astronode_command::cfg_r_get_firmware_minor_version(std::vector<uint8_t> astronode_answer){
    return astronode_answer.at(3);
}

uint8_t Astronode_command::cfg_r_get_firmware_revision(std::vector<uint8_t> astronode_answer){
    return astronode_answer.at(4);
}

bool Astronode_command::cfg_r_get_payload_ack(std::vector<uint8_t> astronode_answer){
    return astronode_answer.at(5) & 1;
}

bool Astronode_command::cfg_r_get_add_geolocation(std::vector<uint8_t> astronode_answer){
   return astronode_answer.at(5) & 2;
}

bool Astronode_command::cfg_r_get_ephemeris_enabled(std::vector<uint8_t> astronode_answer){
    return astronode_answer.at(5) & 4;
}

bool Astronode_command::cfg_r_get_deep_sleep_enabled(std::vector<uint8_t> astronode_answer){
    return astronode_answer.at(5) & 8;
}

bool Astronode_command::cfg_r_get_payload_ack_evt_pin_enabled(std::vector<uint8_t> astronode_answer){
    return astronode_answer.at(7) & 1;
}

bool Astronode_command::cfg_r_get_reset_notification_evt_pin_enabled(std::vector<uint8_t> astronode_answer){
    return astronode_answer.at(7) & 2;
}

bool Astronode_command::cfg_r_get_command_available_evt_pin_enabled(std::vector<uint8_t> astronode_answer){
    return astronode_answer.at(7) & 4;
}

bool Astronode_command::cfg_r_get_message_transmission_pending_evt_pin_enabled(std::vector<uint8_t> astronode_answer){
    return astronode_answer.at(7) & 8;
}

std::vector<uint8_t> Astronode_command::rtc_r_build_command(void){
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    std::vector<uint8_t> data = {ASTRONODE_OP_CODE_RTC_RR};
    return data;
}

uint32_t Astronode_command::rtc_r_get_rtc_time(std::vector<uint8_t> astronode_answer){
    uint32_t rtc_time = (uint32_t)astronode_answer.at(3) << 24;
    rtc_time += (uint32_t)astronode_answer.at(2) << 16;
    rtc_time += (uint32_t)astronode_answer.at(1) << 8;
    rtc_time += (uint32_t)astronode_answer.at(0);
    return rtc_time;
}

std::vector<uint8_t> Astronode_command::nco_r_build_command(void){
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    std::vector<uint8_t> data = {ASTRONODE_OP_CODE_NCO_RR};
    return data;
}

uint32_t Astronode_command::nco_r_get_time_to_next_pass(std::vector<uint8_t> astronode_answer){
    uint32_t next_pass = (uint32_t)astronode_answer.at(3) << 24;
    next_pass += (uint32_t)astronode_answer.at(2) << 16;
    next_pass += (uint32_t)astronode_answer.at(1) << 8;
    next_pass += (uint32_t)astronode_answer.at(0);
    return next_pass;
}

std::vector<uint8_t> Astronode_command::mgi_r_build_command(void){
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    std::vector<uint8_t> data = {ASTRONODE_OP_CODE_DGI_RR};
    return data;
}

std::vector<uint8_t> Astronode_command::msn_r_build_command(void){
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    std::vector<uint8_t> data = {ASTRONODE_OP_CODE_DSN_RR};
    return data;
}

std::vector<uint8_t> Astronode_command::mpn_r_build_command() {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    std::vector<uint8_t> data = {ASTRONODE_OP_CODE_MPN_RR};
    return data;
}

std::vector<uint8_t> Astronode_command::pld_e_build_command(uint16_t payload_id, const std::string payload_data){
    std::cout << __PRETTY_FUNCTION__ <<std::endl;

    // payload_id is converted into two characters. ex. 1001 = 0x03E9 = {0x03, 0xE9}
    std::string s_payload_id;
    s_payload_id.resize(2);
    s_payload_id[0] = (uint8_t)(payload_id>>8);
    s_payload_id[1] = (uint8_t)(payload_id & 0xFF);

    std::string tmp_data = s_payload_id + payload_data;
    std::vector<uint8_t> data(tmp_data.begin(), tmp_data.end());
    data.insert(data.begin(), ASTRONODE_OP_CODE_PLD_ER);
    return data;
}

uint16_t Astronode_command::pld_e_get_payload_id(std::vector<uint8_t> astronode_answer){
    // ex.  {0x03, 0xE9} = 0x03E9 = 1001
    return  (astronode_answer.at(0) << 8) + astronode_answer.at(1);
}

std::vector<uint8_t> Astronode_command::pld_d_build_command(void){
    std::cout << __PRETTY_FUNCTION__ <<std::endl;
    std::vector<uint8_t> data = {ASTRONODE_OP_CODE_PLD_DR};
    return data;
}

uint16_t Astronode_command::pld_d_get_payload_id(std::vector<uint8_t> astronode_answer){
    // ex.  {0x03, 0xE9} = 0x03E9 = 1001
    return  (astronode_answer.at(0) << 8) + astronode_answer.at(1);;
}

std::vector<uint8_t> Astronode_command::pld_f_build_command(void){
    std::cout << __PRETTY_FUNCTION__ <<std::endl;
    std::vector<uint8_t> data = {ASTRONODE_OP_CODE_PLD_FR};
    return data;
}

std::vector<uint8_t> Astronode_command::geo_w_build_command(int32_t lat, int32_t lng){
    std::cout << __PRETTY_FUNCTION__ <<std::endl;
    std::vector<uint8_t> data = {ASTRONODE_OP_CODE_GEO_WR};

    for(int i = 0; i < 4; i++){
        data.insert(data.end(), (uint8_t) (lat >> (i * 8)));
    }

    for(int i = 0; i < 4; i++){
        data.insert(data.end(), (uint8_t) (lng >> (i * 8)));
    }
    return data;
}

std::vector<uint8_t> Astronode_command::evt_r_build_command(void){
    std::cout << __PRETTY_FUNCTION__ <<std::endl;
    std::vector<uint8_t> data = {ASTRONODE_OP_CODE_EVT_RR};
    return data;
}

bool Astronode_command::evt_r_get_sak_available(std::vector<uint8_t> astronode_answer){
    if(astronode_answer.size() != 1){
        throw "evt_ra wrong size";
    }
    return astronode_answer.back() & 0x1;
}

bool Astronode_command::evt_r_get_module_reset(std::vector<uint8_t> astronode_answer){
    if(astronode_answer.size() != 1){
        throw "evt_ra wrong size";
    }
    return astronode_answer.back() & 0x2;
}

bool Astronode_command::evt_r_get_command_available(std::vector<uint8_t> astronode_answer){
    if(astronode_answer.size() != 1){
        throw "evt_ra wrong size";
    }
    return astronode_answer.back() & 0x4;
}

bool Astronode_command::evt_r_get_message_transmit_pending(std::vector<uint8_t> astronode_answer){
    if(astronode_answer.size() != 1){
        throw "evt_ra wrong size";
    }
    return astronode_answer.back() & 0x8;
}

std::vector<uint8_t> Astronode_command::sak_r_build_command(void){
    std::cout << __PRETTY_FUNCTION__ <<std::endl;
    std::vector<uint8_t> data = {ASTRONODE_OP_CODE_SAK_RR};
    return data;
}

uint16_t Astronode_command::sak_r_get_payload_id(std::vector<uint8_t> astronode_answer){
    // ex.  {0x03, 0xE9} = 0x03E9 = 1001
    return  (astronode_answer.at(0) << 8) + astronode_answer.at(1);;
}

std::vector<uint8_t> Astronode_command::sak_c_build_command(void){
    std::cout << __PRETTY_FUNCTION__ <<std::endl;
    std::vector<uint8_t> data = {ASTRONODE_OP_CODE_SAK_CR};
    return data;
}

std::vector<uint8_t> Astronode_command::cmd_r_build_command(void){
    std::cout << __PRETTY_FUNCTION__ <<std::endl;
    std::vector<uint8_t> data = {ASTRONODE_OP_CODE_CMD_RR};
    return data;
}

uint32_t Astronode_command::cmd_r_get_created_date(std::vector<uint8_t> astronode_answer){
    // 0x03C26700 becomes 63072000
    uint32_t created_date = (uint32_t)astronode_answer.at(0) << 24;
    created_date += (uint32_t)astronode_answer.at(1)<<16;
    created_date += (uint32_t)astronode_answer.at(2)<<8;
    created_date += (uint32_t)astronode_answer.at(3);
    return created_date;
}

std::vector<uint8_t> Astronode_command::cmd_r_get_payload(std::vector<uint8_t> astronode_answer){
    std::vector<uint8_t> payload(astronode_answer.begin()+4, astronode_answer.end());
    return payload;
}

std::vector<uint8_t> Astronode_command::cmd_c_build_command(void){
    std::cout << __PRETTY_FUNCTION__ <<std::endl;
    std::vector<uint8_t> data = {ASTRONODE_OP_CODE_CMD_CR};
    return data;
}

std::vector<uint8_t> Astronode_command::res_c_build_command(void){
    std::cout << __PRETTY_FUNCTION__ <<std::endl;
    std::vector<uint8_t> data = {ASTRONODE_OP_CODE_RES_CR};
    return data;
}

std::vector<uint8_t> Astronode_command::val_w_build_command(void){
    std::cout << __PRETTY_FUNCTION__  << std::endl;
    std::vector<uint8_t> data = {ASTRONODE_OP_CODE_VAL_WR};
    return data;
}

std::vector<uint8_t> Astronode_command::ttx_s_build_command(uint8_t transmit_duration_sec){
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    std::vector<uint8_t> data = {ASTRONODE_OP_CODE_TTX_SR};
    data.insert(data.end(), transmit_duration_sec);
    return data;
}



