#include "Astronode_command.h"
#include <iostream>

Astronode_command::astronode_error_code Astronode_command::get_answer_error_code(Transport_layer::answer_t ans){
    if(ans.answer_id == 0xFF){
        // TODO check param size
        uint16_t error_code = (ans.answer_parameters.at(0) << 8 ) | ans.answer_parameters.at(1);
        return static_cast<Astronode_command::astronode_error_code> (error_code);
    } else{
        return ASTRONODE_ERR_CODE_OK;
    }
}

std::vector<uint8_t>  Astronode_command::cfg_w_build_command(uint8_t payload_ack_bit, uint8_t add_geo_bit, uint8_t enable_ephemeris_bit, uint8_t deep_sleep_enabled_bit, uint8_t payload_ack_evt_pin_bit, uint8_t reset_notif_evt_pin_bit){
    std::cout << __PRETTY_FUNCTION__ <<std::endl;
    uint8_t byte0 = ((deep_sleep_enabled_bit & 0x01) << 3) | ((enable_ephemeris_bit & 0x01)<<2) | ((add_geo_bit & 0x01)<<1) | (payload_ack_bit & 0x01);
    uint8_t byte1 = 0;
    uint8_t byte2 = ((reset_notif_evt_pin_bit & 0x01)<<1) | (payload_ack_evt_pin_bit & 0x01);
    return {ASTRONODE_OP_CODE_CFG_WR, byte0, byte1, byte2};
}

std::vector<uint8_t> Astronode_command::wif_w_build_command(std::string wlan_ssid, std::string wlan_key, std::string auth_token){
    std::cout << __PRETTY_FUNCTION__ <<std::endl;
    wlan_ssid.insert(wlan_ssid.end(), SSID_LENGTH - wlan_ssid.size(), '\0');    // zeros padding
    wlan_key.insert(wlan_key.end(), PASSWORD_LENGTH - wlan_key.size(), '\0');   // zeros padding
    auth_token.insert(auth_token.end(), TOKEN_LENGTH - auth_token.size(), '\0');// zeros padding
    std::string tmp_data = wlan_ssid + wlan_key + auth_token;
    std::vector<uint8_t> data(tmp_data.begin(), tmp_data.end());
    data.insert(data.begin(), ASTRONODE_OP_CODE_WIF_WR);
    return data;
}

std::vector<uint8_t> Astronode_command::ssc_w_build_command(uint8_t sat_period_enum, uint8_t enable_search){
    std::cout << __PRETTY_FUNCTION__ <<std::endl;
    std::vector<uint8_t> data = {ASTRONODE_OP_CODE_SSC_WR};
    data.insert(data.end(), sat_period_enum);
    data.insert(data.end(), enable_search == 1 ? 1 : 0);
    return data;
}

std::vector<uint8_t> Astronode_command::cfg_s_build_command(void){
    std::cout << __PRETTY_FUNCTION__ <<std::endl;
    std::vector<uint8_t> data = {ASTRONODE_OP_CODE_CFG_SR};
    return data;
}

std::vector<uint8_t> Astronode_command::cfg_f_build_command(void){
    std::cout << __PRETTY_FUNCTION__ <<std::endl;
    std::vector<uint8_t> data = {ASTRONODE_OP_CODE_CFG_FR};
    return data;
}

std::vector<uint8_t> Astronode_command::cfg_r_build_command(void){
    std::cout << __PRETTY_FUNCTION__ <<std::endl;
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
